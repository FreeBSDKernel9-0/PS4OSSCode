#define LIBRARY_IMPL  (1)
#include "MediaFile.h"
#include "Common.h"

#include "MathUtil.h"

#include "AppFilmManager.h"

#if defined (WIN32)
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <ios>
#define snprintf _snprintf
#endif

#if defined(PLATFORM_MARMALADE) || defined (WIN32)
#define PRId64       "I64d"
#define PRIi64       "I64i"
#define PRIdLEAST64  "I64d"
#define PRIiLEAST64  "I64i"
#define PRIdFAST64   "I64d"
#define PRIiFAST64   "I64i"
#endif


extern "C"
{
#include "libavutil/imgutils.h"
#include "libavutil/timestamp.h"
#include "libavcodec/avcodec.h"
#include "libavutil/samplefmt.h"
#include "libavutil/opt.h"
#include "libavutil/mathematics.h"
#include "libavutil/dict.h"
}

#if defined(mvaden)
#include <perf.h>
#endif
#include <string.h>
#include <iostream>

PRX_INTERFACE void clMediaFile::InitializeFFMpeg()
{

	av_register_all();
#if defined(_DEBUG)
	av_log_set_level(AV_LOG_DEBUG);
#else
	av_log_set_level(AV_LOG_QUIET);
#endif
}

#define MIN_SEEK_FRAME (m_videoDecCtx->gop_size)

uint8_t	clMediaFile::m_tempBuffer[TEMP_BUFFER_WIDTH*TEMP_BUFFER_HEIGHT*4];
nmThread::clCriticalSectionSimple clMediaFile::m_criticalSectionMediaFile;
//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::ConvertVideoPtsToMS(int64_t pts)
{
	double tsms = ( (double)pts * (double)m_fmtCtx->streams[m_videoStreamIdx]->time_base.num) / ( (double)m_fmtCtx->streams[m_videoStreamIdx]->time_base.den);
	int ms =  static_cast<int>((float)tsms * 1000.0f);
	return ms;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::ConvertAudioPtsToMS(int64_t pts)
{
	double tsms = ( (double)pts * (double)m_fmtCtx->streams[m_audioStreamIdx]->time_base.num) / ( (double)m_fmtCtx->streams[m_audioStreamIdx]->time_base.den);
	int ms =  static_cast<int>((float)tsms * 1000.0f);
	return ms;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::GetCurrentVideoTimestamp()
{
	return ConvertVideoPtsToMS(m_currentPts);
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::GetCurrentAudioTimestamp()
{
	return m_bHasAudio ? ConvertAudioPtsToMS(m_currentAudioPts) : 0 ;
}

//int clMediaFile::ConvertMSToPts(int64_t ms)
//{
//	double pts = ( (double)pts * (double)m_fmtCtx->streams[m_videoStreamIdx]->time_base.den) / ( (double)m_fmtCtx->streams[m_videoStreamIdx]->time_base.num);
//	int ms =  ((float)tsms * 1000.0f);
//	return ms;
//}

//----------------------------------------------------------------------------------------------------------------------
// ctor
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE clMediaFile::clMediaFile(): m_sampleCallback(NULL), m_fmtCtx(NULL), m_videoCodec(NULL), m_audioCodec(NULL), m_videoStream(NULL), 
	m_audioStream(NULL), m_videoDecCtx(NULL), m_audioDecCtx(NULL),  m_frame(NULL), m_inputPts(0), m_inputDts(0), 
	m_writeFmtCtx(NULL), m_outputFormat(NULL), m_outputVideoStream(NULL), m_outputAudioStream(NULL), m_outputPts(0), m_SWSContextToRGB(NULL), 
	m_SWSContextYUV420PToYUV(NULL), m_SWSContextToYUV(NULL), 
	m_SwrContext(NULL), m_audioDstData(NULL), m_videoStreamIdx(-1), m_audioStreamIdx(-1), m_videoFrameCount(0), m_outputWidth(1280), m_outputHeight(720), m_isEOF(false), 
	m_opened(false),m_currentPts(0), m_currentAudioPts(0), m_bHasAudio(true), m_audioFormat(kInteger16), m_minPts(0), 
#if defined(YUV_TEXTURES)
	m_bConvertToRgb(false), 
#else
	m_bConvertToRgb(true), 
#endif
	m_nBytesPerPixel(2),
	m_nVideoThreadCount(VIDEO_THREAD_COUNT),
	m_nAudioThreadCount(AUDIO_THREAD_COUNT)

{
	//RedirectIOToConsole();
	//printf("Test \n");
	av_register_all();

	// Make sure all the packet members are NULL or zero
	memset(&m_pkt, 0, sizeof(m_pkt));
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE clMediaFile::~clMediaFile()
{

}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::Close()
{
	// Some av_* functions are not thread safe
	nmThread::clCriticalSectionSimpleLock Lock(m_criticalSectionMediaFile);

	if(m_opened == false)
		return;
	m_opened = false;

	av_frame_free(&m_frame);
		
	if(m_videoDecCtx != NULL)
		avcodec_close(m_videoDecCtx);

	if (m_audioDecCtx)
		avcodec_close(m_audioDecCtx);

	if (m_fmtCtx != NULL)
		avformat_close_input(&m_fmtCtx);
	else
		FF_TRACE("ERROR: AVFormatContext is NULL - avformat_close_input() skipped\n");

	if (m_audioDstData != NULL && m_audioDstData[0] != NULL)
		av_freep(&m_audioDstData[0]);
	else
		FF_TRACE("ERROR: m_audioDstData is NULL - av_freep() skipped\n");

	if (m_audioDstData != NULL)
		av_free(m_audioDstData);
	else
		FF_TRACE("ERROR: m_audioDstData is NULL - av_free() skipped\n");
	
	if(m_SwrContext != NULL)
		swr_free(&m_SwrContext);
	else
		FF_TRACE("ERROR: m_SwrContext is NULL - swr_free() skipped\n");

	if(m_SWSContextToRGB != NULL)
		sws_freeContext(m_SWSContextToRGB);
	else
		FF_TRACE("ERROR: m_SWSContextToRGB is NULL - sws_freeContext() skipped\n");

	if(m_SWSContextYUV420PToYUV != NULL)
		sws_freeContext(m_SWSContextYUV420PToYUV);
	else
		FF_TRACE("ERROR: m_SWSContextYUV420PToYUV is NULL - sws_freeContext() skipped\n");

	if(m_SWSContextToYUV != NULL)
		sws_freeContext(m_SWSContextToYUV);
	else
		FF_TRACE("ERROR: m_SWSContextToYUV is NULL - sws_freeContext() skipped\n");

	if (&m_pkt != NULL )
		av_free_packet(&m_pkt);
	else
		FF_TRACE("ERROR: &m_pkt is NULL - av_free_packet() skipped\n");

	m_opened = false;
}


//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::Open(const char* filename, int streamFlags)
{
	// Some av_* functions (avcodec_open2) are not thread safe
	nmThread::clCriticalSectionSimpleLock Lock(m_criticalSectionMediaFile);

	m_nBytesPerPixel = m_bConvertToRgb ? 4 : 2;

	//if (avformat_open_input(&m_fmtCtx, "/app0/GOPR0019.MP4", NULL, NULL) < 0)
	if (avformat_open_input(&m_fmtCtx, filename, NULL, NULL) < 0)
	{
		FF_TRACE("ERROR: Could not open source file: %s\n", filename);
		return -1;
	} 

	//m_fmtCtx->debug = 1;

	/* retrieve stream information */
	if (avformat_find_stream_info(m_fmtCtx, NULL) < 0)
	{
		if (m_fmtCtx != NULL)
			avformat_close_input(&m_fmtCtx);

		FF_TRACE("ERROR: Could not find stream information for file: %s\n", filename);
		return -1;
    }

#if defined(_DEBUG)
	av_dump_format(m_fmtCtx, 0, filename, false);

	FF_TRACE("Dump Stream: There are %d streams\n", m_fmtCtx->nb_streams);
	for (int i = 0; i < m_fmtCtx->nb_streams; ++i)
	{
		if (m_fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			FF_TRACE("Dump Stream: Video Stream: %d\n", i + 1);
		}
		else if (m_fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			FF_TRACE("Dump Stream: Audio Stream: %d\n", i + 1);
		}
		else if (m_fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_DATA)
		{
			FF_TRACE("Dump Stream: Data Stream: %d\n", i + 1);
		}
		else if (m_fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_SUBTITLE)
		{
			FF_TRACE("Dump Stream: Subtitle Stream: %d\n", i + 1);
		}
		else if (m_fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_ATTACHMENT)
		{
			FF_TRACE("Dump Stream: Attachment Stream: %d\n", i + 1);
		}
	}
#endif

	m_filename = std::string(filename);

	//int videoStreamIdx = -1;
	if ( (streamFlags & kVideoStream) &&  OpenCodecContext(&m_videoStreamIdx, AVMEDIA_TYPE_VIDEO, m_nVideoThreadCount) >= 0) 
	{
		m_videoStream = m_fmtCtx->streams[m_videoStreamIdx];
		m_videoDecCtx = m_videoStream->codec;
		
		if(m_outputWidth == 0)
			SetOutputSize(m_videoDecCtx->width, m_videoDecCtx->height);

    }

	if ((streamFlags & kAudioStream) && OpenCodecContext(&m_audioStreamIdx, AVMEDIA_TYPE_AUDIO, m_nAudioThreadCount) >= 0) 
	{
        int nb_planes;

		m_audioStream = m_fmtCtx->streams[m_audioStreamIdx];
		m_audioDecCtx = m_audioStream->codec;
		m_audioDecCtx->thread_count = 1;
		//m_audioDecCtx->sample_fmt = AV_SAMPLE_FMT_FLT;

		nb_planes = av_sample_fmt_is_planar(m_audioDecCtx->sample_fmt) ?
            m_audioDecCtx->channels : 1;
		m_audioDstData = (uint8_t**)av_mallocz(sizeof(uint8_t *) * nb_planes);
		FF_ASSERTMSG(m_audioDstData != NULL, "Could not allocate audio data buffers"); 


		// Set up SWR context once you've got codec information
		m_SwrContext = swr_alloc();
		if(m_audioFormat == kInteger16)
		{
			av_opt_set_int(m_SwrContext, "in_channel_layout",  m_audioDecCtx->channel_layout, 0);
			av_opt_set_int(m_SwrContext, "out_channel_layout", AV_CH_LAYOUT_STEREO,  0); // force stereo
			av_opt_set_int(m_SwrContext, "in_sample_rate",     m_audioDecCtx->sample_rate, 0);
			//av_opt_set_int(m_SwrContext, "out_sample_rate",    m_audioDecCtx->sample_rate, 0);
			av_opt_set_int(m_SwrContext, "out_sample_rate",    48000, 0);
			av_opt_set_sample_fmt(m_SwrContext, "in_sample_fmt",  m_audioDecCtx->sample_fmt, 0);
			av_opt_set_sample_fmt(m_SwrContext, "out_sample_fmt", AV_SAMPLE_FMT_S16,  0);
		}
		else
		{
			switch(m_audioDecCtx->sample_fmt)
			{
				case AV_SAMPLE_FMT_S16:
				case AV_SAMPLE_FMT_S16P:
					m_audioDstFmt = AV_SAMPLE_FMT_S16;
					break;
				case AV_SAMPLE_FMT_FLT:
				case AV_SAMPLE_FMT_FLTP:
					m_audioDstFmt = AV_SAMPLE_FMT_FLT;
					break;
				default:
					m_audioDstFmt = AV_SAMPLE_FMT_FLT;
					break;
			}
			av_opt_set_int(m_SwrContext, "in_channel_layout",  m_audioDecCtx->channel_layout, 0);
			av_opt_set_int(m_SwrContext, "out_channel_layout", m_audioDecCtx->channel_layout,  0);
			av_opt_set_int(m_SwrContext, "in_sample_rate",     m_audioDecCtx->sample_rate, 0);
			//av_opt_set_int(m_SwrContext, "out_sample_rate",    m_audioDecCtx->sample_rate, 0);
			av_opt_set_int(m_SwrContext, "out_sample_rate",    48000, 0);
			av_opt_set_sample_fmt(m_SwrContext, "in_sample_fmt",   m_audioDecCtx->sample_fmt, 0);
			av_opt_set_sample_fmt(m_SwrContext, "out_sample_fmt", AV_SAMPLE_FMT_S16,  0);
		}
		swr_init(m_SwrContext);
    }
	else
	{
		// We wanted audio and it failed
		if (streamFlags & kAudioStream)
		{
			// Close the file
			if (m_fmtCtx != NULL)
				avformat_close_input(&m_fmtCtx);

			m_bHasAudio = false;

			FF_TRACE("ERROR: Could not find audio in the input, aborting\n");
			return -1;
		}
		m_bHasAudio = false;
	}

	/* dump input information to stderr */
	if (m_fmtCtx)
		av_dump_format(m_fmtCtx, 0, m_filename.c_str(), 0);

	if (!m_audioStream && !m_videoStream)
	{
		// Close the file
		if (m_fmtCtx != NULL)
			avformat_close_input(&m_fmtCtx);

        FF_TRACE("ERROR: Could not find audio or video stream in the input, aborting\n");
		return -1;
    }

	m_frame = av_frame_alloc();
	if (!m_frame)
	{
		// Close the file
		if (m_fmtCtx != NULL)
			avformat_close_input(&m_fmtCtx);

		FF_TRACE("ERROR: Could not allocate frame\n");
		return -1;
	}
	
    /* initialize packet, set data to NULL, let the demuxer fill it */
    av_init_packet(&m_pkt);
    m_pkt.data = NULL;
    m_pkt.size = 0;

	if(m_videoDecCtx)
	{
		// create context for scaling

		m_SWSContextToRGB = sws_getContext(m_videoDecCtx->width, m_videoDecCtx->height, m_videoDecCtx->pix_fmt, m_outputWidth, m_outputHeight, AV_PIX_FMT_BGR32, SWS_POINT, 0, 0, 0);
		m_SWSContextYUV420PToYUV = sws_getContext(m_videoDecCtx->width, m_videoDecCtx->height, m_videoDecCtx->pix_fmt, m_outputWidth, m_outputHeight, AV_PIX_FMT_YUYV422, SWS_POINT, 0, 0, 0);
		m_SWSContextToYUV = sws_getContext(m_videoDecCtx->width, m_videoDecCtx->height, AV_PIX_FMT_BGR32, m_outputWidth, m_outputHeight, m_videoDecCtx->pix_fmt, SWS_POINT, 0, 0, 0);
	}

	clMediaFile::clMediaFrame frame;
	if(streamFlags == kAudioStream)
	{
		GetNextAudioFrame(frame);
		while( (frame.size == 0 || frame.framePts == 0) && GetIsEOF() == false )
		{
			GetNextAudioFrame(frame);
		}
	}
	else
	{
		GetNextVideoFrame(frame);
	}

	m_minPts = frame.framePts;
	FreeFrame(frame);
	m_opened = true;
	
	return 0;

}


//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::GetBufferSize()
{
	if(m_bConvertToRgb)
		return avpicture_get_size (AV_PIX_FMT_BGR32, m_outputWidth, m_outputHeight);
	else
		return avpicture_get_size (AV_PIX_FMT_YUYV422, m_outputWidth, m_outputHeight);
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE bool clMediaFile::GetIsEOF()
{
	return m_isEOF;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
int clMediaFile::GetNextAudioFrameInternal(clMediaFrame& frame)
{
	frame.size = 0;
	frame.buffer = 0;
	int gotFrame= 0;
	while(gotFrame == 0)
	{
		int ret = 0;
		if(m_pkt.data != NULL)
		{
			av_free_packet(&m_pkt);
			m_pkt.data = NULL;
		}
		ret = av_read_frame(m_fmtCtx, &m_pkt);
		if(ret < 0)
		{
			char errorString[1024];
			av_make_error_string(errorString,1024,ret);
			//FF_TRACE("AV_READ_FRAME returned error %s\n",errorString);
			m_isEOF = true;

			return -1;
		}
		DecodeAudioPacket(&gotFrame,0,frame);
		if(gotFrame)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
int clMediaFile::GetNextVideoFrameInternal(clMediaFrame& frame)
{
	frame.size = 0;
	frame.buffer = 0;
	int gotFrame= 0;
	while(gotFrame == 0)
	{
		int ret = 0;
		if(m_pkt.data != NULL)
		{
			av_free_packet(&m_pkt);
			m_pkt.data = NULL;
		}
		ret = av_read_frame(m_fmtCtx, &m_pkt);
		if(ret < 0)
		{
			m_isEOF = true;
			return -1;
		}
		DecodeVideoPacket(&gotFrame,0,frame);
		if(gotFrame)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
int clMediaFile::GetNextFrameInternal(clMediaFrame& frame)
{
	frame.size = 0;
	frame.buffer = 0;
	int gotFrame= 0;
	while(gotFrame == 0)
	{
		int ret = 0;
		if(m_pkt.data != NULL)
		{
			av_free_packet(&m_pkt);
			m_pkt.data = NULL;
		}
		ret = av_read_frame(m_fmtCtx, &m_pkt);
		if(ret < 0)
		{
			m_isEOF = true;
			return -1;
		}
		DecodePacket(&gotFrame,0,frame);
		if(gotFrame)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::FreeFrame(clMediaFrame& frame)
{
	frame.size = 0;
	frame.buffer = NULL;
	//NM_TRACE(0,"Freed frame %x\n",frame.buffer);
}


//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::GetNextAudioFrame(clMediaFrame& outFrame)
{

	int ret = GetNextAudioFrameInternal(outFrame);

	if(ret < 0 )
	{
		FreeFrame(outFrame);
		return;
	}
	else if (ret > 0)
	{
		if(m_pkt.stream_index == m_audioStreamIdx)
		{
#if defined(PLATFORM_MARMALADE)
			outFrame.buffer = 0;
			outFrame.size = 0;
			av_freep(&m_audioDstData[0]);
#else
			outFrame.type = AUDIO_FRAME_TYPE;

			av_freep(&m_audioDstData[0]);
			outFrame.size = m_audioDstBufSize;
			outFrame.framePts = m_pkt.pts;
			outFrame.timeStampInMS = clMediaFile::ConvertAudioPtsToMS(m_pkt.pts);
			av_free_packet(&m_pkt);
			//NM_TRACE(0,"---------Allocated Audio Frame %x with pts %d\n", outFrame.buffer,outFrame.pts);
#endif
		}


	}
	else
	{
		outFrame.size = 0;
	}

}
//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::GetNextFrame(clMediaFrame& outFrame)
{

	int ret = GetNextFrameInternal(outFrame);

	if(ret < 0 || (m_pkt.stream_index == m_videoStreamIdx && m_pkt.stream_index == m_audioStreamIdx ) )
	{
		FreeFrame(outFrame);
		return;
	}
	else if (ret > 0)
	{
		if(m_pkt.stream_index == m_videoStreamIdx)
		{
			outFrame.type = VIDEO_FRAME_TYPE;

			FF_ASSERTMSG(outFrame.buffer != NULL, "Error creating frame buffer\n");
			
			outFrame.width = m_outputWidth;
			outFrame.height = m_outputHeight;
			outFrame.framePts = m_pkt.pts;

			
			outFrame.timeStampInMS = clMediaFile::ConvertVideoPtsToMS(m_pkt.pts);
			//NM_TRACE(0,"************* Returning Frame with timestamp %d\n",outFrame.timeStampInMS);

			av_free_packet(&m_pkt);

			//NM_TRACE(0,"*****Allocated video Frame %x with pts %d\n", outFrame.buffer,outFrame.pts);

			//int frameNumber = m_frame->pts 
		}
		else if(m_pkt.stream_index == m_audioStreamIdx)
		{
#if defined(PLATFORM_MARMALADE)
		outFrame.buffer = 0;
		outFrame.size = 0;
		av_freep(&m_audioDstData[0]);
#else
			outFrame.type = AUDIO_FRAME_TYPE;
			
			av_freep(&m_audioDstData[0]);
			outFrame.size = m_audioDstBufSize;
			outFrame.framePts = m_pkt.pts;
			outFrame.timeStampInMS = clMediaFile::ConvertAudioPtsToMS(m_pkt.pts);
			av_free_packet(&m_pkt);
			//NM_TRACE(0,"---------Allocated Audio Frame %x with pts %d\n", outFrame.buffer,outFrame.pts);
#endif
		}


	}
	else
	{
		outFrame.size = 0;
	}
	
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::GetNextVideoFrame(clMediaFrame& outFrame)
{
	if(m_videoStreamIdx == -1)
		return;
	outFrame.type = OTHER_FRAME_TYPE;
	while((outFrame.type != VIDEO_FRAME_TYPE || outFrame.size == 0) && GetIsEOF() == false )
	{
		FreeFrame(outFrame);
		GetNextFrame(outFrame);
	}

}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::SetOutputSize(int width, int height)
{
	m_outputWidth = width;
	m_outputHeight = height;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int64_t clMediaFile::FindPtsPerFrame()
{
	int64_t b= (int64_t)m_fmtCtx->streams[m_videoStreamIdx]->time_base.den * (int64_t)m_fmtCtx->streams[m_videoStreamIdx]->avg_frame_rate.den;
	int64_t c= (int64_t)m_fmtCtx->streams[m_videoStreamIdx]->time_base.num * (int64_t)m_fmtCtx->streams[m_videoStreamIdx]->avg_frame_rate.num;
	int64_t ptsInterval = av_rescale(1, b,c) ;
	ptsInterval = ptsInterval < 0 ? 1001: ptsInterval;
	return ptsInterval;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int64_t clMediaFile::FindOutputAudioPtsPerFrame()
{
	int64_t b=	m_outputAudioStream->time_base.den ;
	int64_t c=	m_outputAudioStream->time_base.num ;
	int64_t ptsInterval = av_rescale(1, b,c) ;
	ptsInterval = ptsInterval < 0 ? 1001: ptsInterval;
	return ptsInterval;
}

PRX_INTERFACE int64_t clMediaFile::ConvertSecondsToVideoPts( float seekPosInSeconds ) 
{
	int64_t tsms = (int64_t)(seekPosInSeconds * 1000.0f);
	int64_t desiredFrameNumber = av_rescale(tsms,m_fmtCtx->streams[m_videoStreamIdx]->time_base.den,m_fmtCtx->streams[m_videoStreamIdx]->time_base.num);
	desiredFrameNumber/=1000;
	return desiredFrameNumber;
}

int64_t clMediaFile::ConvertSecondsToAudioPts( float seekPosInSeconds ) 
{
	int64_t tsms = (int64_t)(seekPosInSeconds * 1000.0f);
	int64_t desiredFrameNumber = av_rescale(tsms,m_fmtCtx->streams[m_audioStreamIdx]->time_base.den,m_fmtCtx->streams[m_audioStreamIdx]->time_base.num);

	double frame = (double)tsms * (double)m_fmtCtx->streams[m_audioStreamIdx]->time_base.den / (double) m_fmtCtx->streams[m_audioStreamIdx]->time_base.num;
	//double ratio = (double)m_fmtCtx->streams[m_audioStreamIdx]->time_base.den / (double) m_fmtCtx->streams[m_audioStreamIdx]->time_base.num;
	desiredFrameNumber = (int64_t)frame;
	desiredFrameNumber/=1000;
	return desiredFrameNumber;
}

PRX_INTERFACE void clMediaFile::SeekToAudioFrame(float seekPosInSeconds)
{
	if(GetHasAudio() == false)
		return;

	int64_t desiredFrameNumber = ConvertSecondsToAudioPts(seekPosInSeconds);
	desiredFrameNumber+=m_minPts;
	float duration = GetAudioDurationInSeconds();
	if(seekPosInSeconds > duration)
		return;

	if(m_audioStream->start_time != AV_NOPTS_VALUE && desiredFrameNumber < this->m_audioStream->start_time)
		desiredFrameNumber = this->m_audioStream->start_time;


	m_isEOF = false;
	int64_t currentPts = m_currentAudioPts;
	int seekFlags = AVSEEK_FLAG_ANY;
	/*if(currentPts > desiredFrameNumber)
	{
		seekFlags |= AVSEEK_FLAG_BACKWARD;
	}*/
	 
	int ret = av_seek_frame(m_fmtCtx,m_audioStreamIdx,m_audioStream->start_time,AVSEEK_FLAG_ANY);
	if(ret < 0)
	{
		char* errStr = av_err2str(ret);
		FF_TRACE("ERROR: %s: error while seeking audio in %s\n", errStr, m_filename.c_str());
	}
	avcodec_flush_buffers(m_fmtCtx->streams[m_audioStreamIdx]->codec);
	if(desiredFrameNumber != this->m_audioStream->start_time)
	{
		ret = av_seek_frame(m_fmtCtx,m_audioStreamIdx,desiredFrameNumber,seekFlags);
		if(ret < 0)
		{
			char* errStr = av_err2str(ret);
			FF_TRACE("ERROR: %s: error while seeking audio in %s\n", errStr, m_filename.c_str());
		}
		avcodec_flush_buffers(m_fmtCtx->streams[m_audioStreamIdx]->codec);
	}
	//avcodec_flush_buffers(m_fmtCtx->streams[m_audioStreamIdx]->codec);
	m_currentAudioPts = desiredFrameNumber;

	return;
}
//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE clMediaFile::clMediaFrame clMediaFile::SeekToClosestKeyFrame(float seekPosInSeconds)
{
	int64_t desiredFrameNumber = ConvertSecondsToVideoPts(seekPosInSeconds);
	desiredFrameNumber = desiredFrameNumber < m_minPts ? m_minPts : desiredFrameNumber;
	float duration = GetDurationInSeconds();
	
	FF_ASSERT(seekPosInSeconds <= duration);


	m_isEOF = false;

	//save off current pts so we can see if we need to manually seek
	int64_t currentPts = m_currentPts;
	bool seekBackwards = false;
	int seekFlags = AVSEEK_FLAG_FRAME;

	if(currentPts > desiredFrameNumber)
	{
		seekFlags |= AVSEEK_FLAG_BACKWARD;
		seekBackwards = true;
	}
	
	clMediaFrame frame;
	frame.size = 0;
	frame.buffer = NULL;
	if(m_videoStreamIdx >=0)
	{
		int64_t pts = 0;


		int64_t ptsInterval = FindPtsPerFrame();
		ptsInterval *= (MIN_SEEK_FRAME);
			
		if( abs(desiredFrameNumber - currentPts)  < ptsInterval)
		{
			return Seek(seekPosInSeconds);
		}

		int ret = 0;
		if( (ret = av_seek_frame(m_fmtCtx,m_videoStreamIdx,desiredFrameNumber,seekFlags)) < 0)
		{
			char errorString[1024];
			av_make_error_string(errorString,1024,ret);
			return Seek(seekPosInSeconds);
		} 
			
		// next frame is a keyframe
		GetNextVideoFrame(frame);
		pts = frame.framePts;
		

		if( (seekBackwards == false && frame.framePts > desiredFrameNumber) || (seekBackwards == true && frame.framePts < desiredFrameNumber) )
		{
			//NM_TRACE(0,"*********** Seeked past desired frame\n");
			// We need to keep the current pts because we seeked past our frame number in a small video this can cause us to be constantly 
			// seeking to the exact keyframe.
			m_currentPts = currentPts;
		}

		return frame;
	}
	else
	{
		return clMediaFrame();
	}
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::SeekBackwards(int64_t desiredFrameNumber)
{
	int64_t pts;
	clMediaFrame frame;
	//int64_t delta = abs(m_currentPts - desiredFrameNumber);
	int64_t minSeek = (FindPtsPerFrame()  * MIN_SEEK_FRAME ) + FindPtsPerFrame();

	//int64_t seekFrame = desiredFrameNumber < minSeek ? 0 : desiredFrameNumber - minSeek;
	//ret = av_seek_frame(m_fmtCtx,m_videoStreamIdx,seekFrame,AVSEEK_FLAG_FRAME)) seekFrame = delta < minSeek ? desiredFrameNumber-minSeek : desiredFrameNumber;
	int64_t seekFrame = desiredFrameNumber - minSeek;
	seekFrame = seekFrame < m_minPts ? m_minPts : seekFrame;

	if(av_seek_frame(m_fmtCtx,m_videoStreamIdx,seekFrame,AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD) < 0)
	//if(av_seek_frame(m_fmtCtx,m_videoStreamIdx,0,AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD) < 0)
	{
		FF_TRACE("%s: error while seeking \n", m_filename.c_str());
		int ret = av_seek_frame(m_fmtCtx,m_videoStreamIdx,0,AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD);
		FF_ASSERT(ret > 0);
	} 
	
	if(desiredFrameNumber == 0)
		return;

	m_isEOF = false;
	// get a frame to see our pts

	GetNextVideoFrame(frame);
	pts = frame.framePts;
	FreeFrame(frame);
	if(pts == desiredFrameNumber)
	{
		return;
	}

	// seek back the current key frame interval

	int64_t ptsInterval = FindPtsPerFrame() * MIN_SEEK_FRAME;
	FF_ASSERT(ptsInterval > 0);
	while(pts >= desiredFrameNumber)
	{
		int64_t newSeekPos = desiredFrameNumber - ptsInterval;
		newSeekPos = newSeekPos < 0 ? 0 : pts - ptsInterval;
		if(av_seek_frame(m_fmtCtx,m_videoStreamIdx,newSeekPos,AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD) < 0)
		{
			// seek back to 0 as fallback
			int ret = av_seek_frame(m_fmtCtx,m_videoStreamIdx,0,AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD);
			// if we can't even seek to 0 not sure what we can do
			FF_ASSERT(ret >=0);
			FF_TRACE("ERROR: %s: error while seeking \n", m_filename.c_str());
		} 
		m_isEOF = false;
		frame.size = 0;
		frame.buffer = NULL;
		GetNextVideoFrame(frame);

		pts = frame.framePts;
		FreeFrame(frame);
		ptsInterval += FindPtsPerFrame() * MIN_SEEK_FRAME;

	}
}

//----------------------------------------------------------------------------------------------------------------------
// Seek to the exact start of the media file. This is potentially slow.
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE clMediaFile::clMediaFrame clMediaFile::Seek(float seekPosInSeconds)
{
	int64_t tsms = (int64_t)(seekPosInSeconds * 1000.0f);
	int64_t desiredFrameNumber = av_rescale(tsms,m_fmtCtx->streams[m_videoStreamIdx]->time_base.den,m_fmtCtx->streams[m_videoStreamIdx]->time_base.num);
	desiredFrameNumber/=1000;

	desiredFrameNumber = desiredFrameNumber < m_minPts ? m_minPts : desiredFrameNumber;

	float duration = GetDurationInSeconds();

	//FF_ASSERT(seekPosInSeconds <=duration);
	if(seekPosInSeconds > duration)
		seekPosInSeconds = duration;

	m_isEOF =false;
	//save off current pts so we can see if we need to manually seek
	int64_t currentPts = m_currentPts;
	
	int seekFlags = AVSEEK_FLAG_FRAME;
	bool seekBackwards = false;
	if(currentPts > desiredFrameNumber)
	{
		seekFlags |= AVSEEK_FLAG_BACKWARD;
		seekBackwards = true;
	}
	
	clMediaFrame frame;
	frame.size = 0;
	frame.buffer = NULL;
	if(m_videoStreamIdx >=0)
	{
		int64_t pts = 0;
		if(seekBackwards)
		{
			SeekBackwards(desiredFrameNumber);
			return SeekFrameByFrame(desiredFrameNumber);
		}
		else
		{
			// find the interval of one frame
			int64_t ptsInterval = FindPtsPerFrame();
			ptsInterval *= MIN_SEEK_FRAME;
			
			// try and compute the last keyframe
			int64_t maxFrameNumber = av_rescale((duration*1000),m_fmtCtx->streams[m_videoStreamIdx]->time_base.den,m_fmtCtx->streams[m_videoStreamIdx]->time_base.num);
			int64_t minSeek = ((FindPtsPerFrame()  * MIN_SEEK_FRAME ) + FindPtsPerFrame()) * 1.5;
			maxFrameNumber/=1000;
			maxFrameNumber -= minSeek;

			if(desiredFrameNumber - currentPts  < ptsInterval && desiredFrameNumber < maxFrameNumber)
			{
				clMediaFrame tempFrame =  SeekFrameByFrame(desiredFrameNumber);
				if(tempFrame.size > 0)
					return tempFrame;
			}

			int ret = 0;
			//NM_TRACE(0,"========================= Starting Seek\n");
			// we need to make sure we are not trying to find a keyframe past the last keyframe

			int64_t seekFrame = desiredFrameNumber > maxFrameNumber ? maxFrameNumber : desiredFrameNumber;
			// make sure we are not seeking backwards now
			if(seekFrame < m_currentPts)
			{
				SeekBackwards(seekFrame);
			}
			else
			{
				if( (ret = av_seek_frame(m_fmtCtx,m_videoStreamIdx,seekFrame,AVSEEK_FLAG_FRAME)) < 0)

				{
					SeekBackwards(seekFrame);
				}
			}


			// get a frame to see our pts
			frame.buffer = NULL;
			frame.framePts = 0;
			frame.timeStampInMS = 0;
			GetNextVideoFrame(frame);
			pts = frame.framePts;
			FreeFrame(frame);
			//FF_TRACE("ERROR: Seek took us to frame %d\n",seekPosInSeconds, pts);
			if(pts > desiredFrameNumber)
			{
				SeekBackwards(desiredFrameNumber);
			}
		}
			
		clMediaFrame tempFrame =  SeekFrameByFrame(desiredFrameNumber);
		m_currentPts = tempFrame.framePts;
		return tempFrame;

	}
	else
	{
		return frame;
	}
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE clMediaFile::clMediaFrame clMediaFile::SeekFrameByFrame(int64_t desiredFrameNumber)
{
#if defined(mvaden)
	//sceRazorCpuPushMarker("SEEK_SeekFrameByFrame",SCE_RAZOR_COLOR_WHITE,SCE_RAZOR_MARKER_ENABLE_HUD);
#endif
	clMediaFrame frame;
	frame.size = 0;
	frame.buffer = NULL;
	GetNextVideoFrame(frame);
	int64_t pts = frame.framePts;
	//int64_t ptsPerFrame = FindPtsPerFrame();
	clMediaFrame returnFrame = frame;
	while ( pts < desiredFrameNumber)
	{
		//FF_TRACE("ERROR: Decoding forward to desired position %d currently at %d\n",desiredFrameNumber, pts);
		GetNextVideoFrame(frame);
		if(frame.size > 0)
			returnFrame = frame;
		
		if(frame.framePts <= pts && frame.size > 0)
		{
			FF_ASSERT(0);
			//break;
		}
		if(m_isEOF)
			break;
		pts = frame.framePts;
	}
#if defined(mvaden)
	//sceRazorCpuPopMarker();
#endif
	return returnFrame;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE float clMediaFile::GetDurationInSeconds()
{
	//double seconds = ((double)m_fmtCtx->duration)/((double)(AV_TIME_BASE));
	//return (float)seconds;
	double rational =((double)(m_fmtCtx->streams[m_videoStreamIdx]->time_base.num))/((double)(m_fmtCtx->streams[m_videoStreamIdx]->time_base.den));
	double seconds = ((double)m_fmtCtx->streams[m_videoStreamIdx]->duration)*rational;
	return (float)seconds;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE float clMediaFile::GetAudioDurationInSeconds()
{
	double rational =((double)(m_fmtCtx->streams[m_audioStreamIdx]->time_base.num))/((double)(m_fmtCtx->streams[m_audioStreamIdx]->time_base.den));
	double seconds = ((double)m_fmtCtx->streams[m_audioStreamIdx]->duration)*rational;
	return (float)seconds;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE bool clMediaFile::GenerateThumbnails(const char* filename, 
	                                 float startPosInSeconds, 
									 float timeBetweenSamplesInSeconds, 
									 int thumbCount, 
									 int width, 
									 int height,
									 std::vector<uint8_t*>& aThumbs)
{
	clMediaFile mediaFile;
	mediaFile.SetDecodeToRGB(true);
	mediaFile.SetOutputSize(width,height);

	bool bRet = false;
	if( mediaFile.Open(filename,kVideoStream) < 0)
	{
		FF_TRACE("ERROR: Thumbnails not generated could not open file.\n");
		return bRet;
	}
	for(int i=0;i<thumbCount;++i)
	{
		//uint8_t* src = NULL;
		clMediaFile::clMediaFrame frame;

		frame = mediaFile.Seek(startPosInSeconds + (i*timeBetweenSamplesInSeconds));
		//frame = mediaFile.SeekToClosestKeyFrame(startPosInSeconds + (i*timeBetweenSamplesInSeconds));

		if (frame.size <= 0)
		{
			FF_TRACE("ERROR: generating thumb %d\n", i);
			break;
		}

		int size = mediaFile.GetBufferSize();

		// Using nomad memory malloc wrapper - djt
		uint8_t* dst = (uint8_t*)malloc(size);
		memcpy(dst, frame.buffer.get(), size);

		aThumbs.push_back(dst);
		FreeFrame(frame);

		bRet = true;
	}

	mediaFile.Close();
	return bRet;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::OpenCodecContext(int *stream_idx, enum AVMediaType type, int threadCount)
{
    int ret;
    AVStream *st;
    AVCodecContext *dec_ctx = NULL;
    AVCodec *dec = NULL;

    ret = av_find_best_stream(m_fmtCtx, type, -1, -1, NULL, 0);
    if (ret < 0) {
        FF_TRACE("ERROR: Could not find %s stream in input file '%s'\n",
			av_get_media_type_string(type), m_filename.c_str());
        return ret;
    } else {
        *stream_idx = ret;
		st = m_fmtCtx->streams[*stream_idx];

        /* find decoder for the stream */
        dec_ctx = st->codec;
        dec = avcodec_find_decoder(dec_ctx->codec_id);
        if (!dec) {
            FF_TRACE("ERROR: Failed to find %s codec\n",
                    av_get_media_type_string(type));
            return ret;
        }

		dec_ctx->thread_count = threadCount;
        if ((ret = avcodec_open2(dec_ctx, dec, NULL)) < 0) {
            FF_TRACE("ERROR: Failed to open %s codec\n",
                    av_get_media_type_string(type));
            return ret;
        }

    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::DecodeAudioPacket(int *got_frame, int cached,clMediaFrame& outFrame)
{
    int ret = 0;
	*got_frame = 0;

	if (m_pkt.stream_index == m_audioStreamIdx) 
	{
        /* decode audio frame */
		outFrame.size = m_audioDstBufSize;

		ret = avcodec_decode_audio4(m_audioDecCtx, m_frame, got_frame, &m_pkt);
        if (ret < 0) {
            FF_TRACE("ERROR: decoding audio frame\n");
            return ret;
        }

        if (*got_frame) {
            /*printf("audio_frame%s n:%d nb_samples:%d pts:%s\n",
                   cached ? "(cached)" : "",
                   audio_frame_count++, frame->nb_samples,
                   av_ts2timestr(frame->pts, &audio_dec_ctx->time_base));*/

			int64_t out_samples = av_rescale_rnd(swr_get_delay(m_SwrContext, 48000) + m_frame->nb_samples, m_audioDecCtx->sample_rate, 48000, AV_ROUND_UP);
			if(m_audioFormat == kInteger16)
				ret = av_samples_alloc(m_audioDstData,NULL, 2, out_samples, AV_SAMPLE_FMT_S16, 1); // hard coded to stereo
			else
				ret = av_samples_alloc(m_audioDstData, NULL, av_frame_get_channels(m_frame), out_samples, m_audioDstFmt, 1);

			FF_ASSERTMSG(ret >=0, "Could not allocate audio buffer\n"); 

            /* TODO: extend return code of the av_samples_* functions so that this call is not needed */
			if(m_audioFormat == kInteger16)
				m_audioDstBufSize = av_samples_get_buffer_size(NULL, 2, out_samples, AV_SAMPLE_FMT_S16, 1); // froce stereo
			else
				m_audioDstBufSize = av_samples_get_buffer_size(NULL, av_frame_get_channels(m_frame), out_samples, m_audioDstFmt, 1);

			swr_convert(m_SwrContext, m_audioDstData, out_samples, (const uint8_t**)m_frame->extended_data, m_frame->nb_samples);
			std::shared_ptr<uint8_t> temp((uint8_t*)av_memdup(m_audioDstData[0],m_audioDstBufSize),av_free);
			outFrame.buffer = temp;
			m_currentAudioPts = m_pkt.pts;
			FF_ASSERT(outFrame.buffer);
        }
    }
    return ret;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::DecodeVideoPacket(int *got_frame, int cached,clMediaFrame& outFrame)
{
    int ret = 0;
	*got_frame = 0;
    if (m_pkt.stream_index == m_videoStreamIdx) 
	{
		av_frame_unref(m_frame);

		ret = avcodec_decode_video2(m_videoDecCtx, m_frame, got_frame, &m_pkt);

        if (*got_frame) 
		{
			if(m_bConvertToRgb)
				outFrame.size = avpicture_get_size (AV_PIX_FMT_BGR32, m_outputWidth, m_outputHeight);
			else
				outFrame.size = avpicture_get_size (AV_PIX_FMT_YUYV422, m_outputWidth, m_outputHeight);

			std::shared_ptr<uint8_t> temp( (uint8_t*)av_malloc(outFrame.size),av_free);
			outFrame.buffer = temp; 
			FF_ASSERT(outFrame.buffer);
			//NM_TRACE(0,"Packet pts = %d\n",m_pkt.pts);
			uint8_t* tempArray[1];
			tempArray[0] = outFrame.buffer.get();
			int tempLineSize[AV_NUM_DATA_POINTERS];
			memset(tempLineSize,0,sizeof (tempLineSize));
			tempLineSize[0] = m_outputWidth * m_nBytesPerPixel;
			if(m_bConvertToRgb)
				sws_scale(m_SWSContextToRGB, m_frame->data, m_frame->linesize, 0, m_videoDecCtx->height, &tempArray[0], tempLineSize );
			else
				sws_scale(m_SWSContextYUV420PToYUV, m_frame->data, m_frame->linesize, 0, m_videoDecCtx->height, &tempArray[0], tempLineSize );
			//memcpy(outFrame.buffer, m_frame->data[0], m_frame->linesize[0]*m_videoDecCtx->height);
			m_currentPts = m_pkt.pts;
        }
	}

    return ret;
}
//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::DecodePacket(int *got_frame, int cached,clMediaFrame& outFrame)
{
    int ret = 0;
	*got_frame = 0;
    if (m_pkt.stream_index == m_videoStreamIdx) 
	{
		av_frame_unref(m_frame);

		ret = avcodec_decode_video2(m_videoDecCtx, m_frame, got_frame, &m_pkt);

        if (*got_frame) 
		{
			if(m_bConvertToRgb)
				outFrame.size = avpicture_get_size (AV_PIX_FMT_BGR32, m_outputWidth, m_outputHeight);
			else
				outFrame.size = avpicture_get_size (AV_PIX_FMT_YUYV422, m_outputWidth, m_outputHeight);

			outFrame.buffer = std::shared_ptr<uint8_t>((uint8_t*)av_malloc(outFrame.size),av_free); 
			FF_ASSERT(outFrame.buffer);
			//NM_TRACE(0,"Packet pts = %d\n",m_pkt.pts);
			uint8_t* tempArray[1];
			tempArray[0] = outFrame.buffer.get();
			int tempLineSize[AV_NUM_DATA_POINTERS];
			memset(tempLineSize,0,sizeof (tempLineSize));
			tempLineSize[0] = m_outputWidth * m_nBytesPerPixel;
			if(m_bConvertToRgb)
				sws_scale(m_SWSContextToRGB, m_frame->data, m_frame->linesize, 0, m_videoDecCtx->height, &tempArray[0], tempLineSize);
			else
				sws_scale(m_SWSContextYUV420PToYUV, m_frame->data, m_frame->linesize, 0, m_videoDecCtx->height, &tempArray[0], tempLineSize);

			m_currentPts = m_pkt.pts;
        }
	}

	else if (m_pkt.stream_index == m_audioStreamIdx) 
	{
        /* decode audio frame */
		outFrame.size = m_audioDstBufSize;

		ret = avcodec_decode_audio4(m_audioDecCtx, m_frame, got_frame, &m_pkt);
        if (ret < 0) {
            FF_TRACE("ERROR: decoding audio frame\n");
            return ret;
        }

        if (*got_frame) {
            /*printf("audio_frame%s n:%d nb_samples:%d pts:%s\n",
                   cached ? "(cached)" : "",
                   audio_frame_count++, frame->nb_samples,
                   av_ts2timestr(frame->pts, &audio_dec_ctx->time_base));*/

			if(m_audioFormat == kInteger16)
				ret = av_samples_alloc(m_audioDstData, &m_audioDstLinesize, av_frame_get_channels(m_frame), m_frame->nb_samples, AV_SAMPLE_FMT_S16, 1);
			else
				ret = av_samples_alloc(m_audioDstData, &m_audioDstLinesize, av_frame_get_channels(m_frame), m_frame->nb_samples, m_audioDstFmt, 1);

			FF_ASSERTMSG(ret >=0, "Could not allocate audio buffer\n"); 

            /* TODO: extend return code of the av_samples_* functions so that this call is not needed */
			if(m_audioFormat == kInteger16)
				m_audioDstBufSize = av_samples_get_buffer_size(NULL, av_frame_get_channels(m_frame), m_frame->nb_samples, AV_SAMPLE_FMT_S16, 1);
			else
				m_audioDstBufSize = av_samples_get_buffer_size(NULL, av_frame_get_channels(m_frame), m_frame->nb_samples, m_audioDstFmt, 1);

            /* copy audio data to destination buffer:
             * this is required since rawaudio expects non aligned data */
			//av_samples_copy(m_audioDstData, m_frame->data, 0, 0, m_frame->nb_samples, av_frame_get_channels(m_frame), (AVSampleFormat)m_frame->format);
			//uint8_t* tempArray[1];
			//tempArray[0] = outFrame.buffer;

			swr_convert(m_SwrContext, m_audioDstData, m_frame->nb_samples, (const uint8_t**)m_frame->extended_data, m_frame->nb_samples);
			std::shared_ptr<uint8_t> tempMemory((uint8_t*)av_memdup(m_audioDstData[0],m_audioDstBufSize), av_free);
			outFrame.buffer = tempMemory;
			m_currentAudioPts = m_pkt.pts;
			FF_ASSERT(outFrame.buffer);
        }
    }
	else
	{
		 //fprintf(stdout, "Non av frame\n");
	}


    return ret;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::GetAudioSampleRate()
{
	if(m_audioDecCtx != NULL)
		return m_audioDecCtx->sample_rate;
	else
		return -1;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::GetAudioNumChannels()
{
	if(m_audioDecCtx != NULL)
		return m_audioDecCtx->channels;
	else
		return -1;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::GetAudioSampleCount()
{
	if(m_audioDecCtx != NULL)
		return m_audioDecCtx->frame_size;
	else
		return -1;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::SetupWriter(const char* filename, int width, int height) 
{ 
	avcodec_register_all();
	    /* allocate the output media context */
    avformat_alloc_output_context2(&m_writeFmtCtx, NULL, NULL, filename);
    if (!m_writeFmtCtx) 
	{
        FF_TRACE("ERROR: Could not deduce output format from file extension\n");
        return -1;
    }

    m_outputFormat = m_writeFmtCtx->oformat;

	m_videoCodec = avcodec_find_encoder_by_name("libx264");

	m_audioCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
	//m_audioCodec = avcodec_find_encoder_by_name("aac");

    /* Add the audio and video streams using the default format codecs
     * and initialize the codecs. */
    m_outputVideoStream = NULL;
    m_outputAudioStream = NULL;

    if (m_outputFormat->video_codec != AV_CODEC_ID_NONE) 
	{
		m_outputVideoStream = AddStream(m_videoStream, m_videoCodec);
    }
    if (m_outputFormat->audio_codec != AV_CODEC_ID_NONE) 
	{
		m_outputAudioStream = AddStream(m_audioStream, m_audioCodec);
    }
	
	// fill all required fields in avCodecCtx
	AVDictionary * opt = NULL;
	avcodec_open2(m_outputVideoStream->codec, m_videoCodec, &opt);

	m_outputVideoStream->time_base = m_videoStream->time_base;

	// fill all required fields in avCodecCtx
	opt = NULL;
	avcodec_open2(m_outputAudioStream->codec, m_audioCodec, &opt);

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::Transcode(const char* filename, double startPosInSeconds, double endPosInSeconds)
{
	int ret = 0;

	ret = SetupWriter(filename,m_outputWidth,m_outputHeight);
    /* open the output file, if needed */
    if (!(m_outputFormat->flags & AVFMT_NOFILE)) 
	{
        ret = avio_open(&m_writeFmtCtx->pb, filename, AVIO_FLAG_WRITE);
        if (ret < 0) 
		{
            FF_TRACE("ERROR: Could not open '%s': %d\n", filename);
            return -1;
        }
    }

    /* Write the stream header, if any. */
    ret = avformat_write_header(m_writeFmtCtx, NULL);
    if (ret < 0) 
	{
        FF_TRACE("ERROR: occurred when writing header: %d\n", ret);
        return -1;
    }

    //if (m_rgbFrame)
    //    m_rgbFrame->pts = 0;
	if(m_frame)
		m_frame->pts = 0;

	int videoFrameNumber = 1;
	m_outputPts = 0;

	if(m_pOutputFrame == NULL)
	{
		m_pOutputFrame = av_frame_alloc();
		if (!m_pOutputFrame)
		{
			// Close the file
			if (m_fmtCtx != NULL)
				avformat_close_input(&m_fmtCtx);

			FF_TRACE("ERROR: Could not allocate frame\n");
			return -1;
		}
	}

	double currentAudioTime = 0;
	double currentVideoTime = 0;

	Seek((float)startPosInSeconds);
    for (;;) {

		clMediaFrame frame;
		GetNextFrame(frame);

		if(frame.size > 0)
		{
			/* write interleaved audio and video frames */
			if (m_pkt.stream_index == m_audioStreamIdx) 
			{
				if(currentAudioTime < endPosInSeconds)
				{
					ret = WriteAudioFrame(frame);
					if(ret < 0)
						return -1;
					currentAudioTime = ((double)ConvertAudioPtsToMS(frame.framePts) / 1000.0f);
				}

			} else  if (m_pkt.stream_index == m_videoStreamIdx )// && m_frame->pict_type !=  AV_PICTURE_TYPE_NONE)
			{
				bool frameWritten = false;
				if(currentVideoTime < endPosInSeconds)
				{
					ret = WriteVideoFrame(frame,(float)(videoFrameNumber++),(float)startPosInSeconds, frameWritten);
					if(ret < 0)
						return -1;
				}

				currentVideoTime = ((double)ConvertVideoPtsToMS(frame.framePts) / 1000.0f) ;
				if(GetHasAudio() == false)
					currentAudioTime = currentVideoTime;
				//m_rgbFrame->pts += av_rescale_q(1, m_outputVideoStream->codec->time_base, m_outputVideoStream->time_base);
				//m_frame->pts++;// = av_rescale_q(1, m_outputVideoStream->codec->time_base, m_outputVideoStream->time_base); 
			}
			
			FreeFrame(frame);
		}
		av_free_packet(&m_pkt);


		if(GetIsEOF() == true || (currentAudioTime > endPosInSeconds && currentVideoTime > endPosInSeconds))
			break;
    }
	int gotFrame=1;
	clMediaFrame frame;
	bool frameWritten;
	// first we have to flush frames still in the decoder
	while(gotFrame > 0)
	{
		DecodePacket(&gotFrame,0,frame);
		if(gotFrame)
			WriteVideoFrame(frame,(float)videoFrameNumber++,(float)startPosInSeconds, frameWritten);
		FreeFrame(frame);
	}

	// next we have to flush frames still in the encoder
	int outsize = 1;
	FreeFrame(frame);
	frameWritten = true;
	while(frameWritten==true)
	{
		WriteVideoFrame(frame,(float)videoFrameNumber++, (float)startPosInSeconds, frameWritten);
	}
    /* Write the trailer, if any. The trailer must be written before you
     * close the CodecContexts open when you wrote the header; otherwise
     * av_write_trailer() may try to use memory that was freed on
     * av_codec_close(). */
	av_write_trailer(m_writeFmtCtx);

    /* Close each codec. */
    if (m_outputVideoStream)
        CloseVideo();
    if (m_outputAudioStream)
        CloseAudio();

	if (!(m_outputFormat->flags & AVFMT_NOFILE))
        /* Close the output file. */
        avio_close(m_writeFmtCtx->pb);

    /* free the stream */
    avformat_free_context(m_writeFmtCtx);

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::CloseVideo()
{
	avcodec_close(m_outputVideoStream->codec);
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::CloseAudio()
{
	avcodec_close(m_outputAudioStream->codec);
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE AVStream * clMediaFile::AddStream(AVStream *srcSt, AVCodec *dstCodec)
{
    AVCodecContext *c;
    AVStream *st;
	AVCodecContext *srcCodecCtx = srcSt->codec;

    st = avformat_new_stream(m_writeFmtCtx, dstCodec);
    if (!st) 
	{
        FF_TRACE("ERROR: Could not allocate stream\n");
        return NULL;
    }
    st->id = m_writeFmtCtx->nb_streams-1;
    c = st->codec;

    switch (dstCodec->type) 
	{
		case AVMEDIA_TYPE_AUDIO:
			st->id = 1;
			enum AVSampleFormat sampleFormat;
			av_opt_get_sample_fmt(m_SwrContext,"out_sample_fmt",0,&sampleFormat);
			c->sample_fmt  = sampleFormat;
			c->bit_rate    = srcCodecCtx->bit_rate;
			c->sample_rate = srcCodecCtx->sample_rate;
			c->channels    = srcCodecCtx->channels;
			c->frame_size = srcCodecCtx->frame_size;
        break;

    case AVMEDIA_TYPE_VIDEO:
        //c->codec_id = codec_id;

		//c->bit_rate = srcCodecCtx->bit_rate;
        /* Resolution must be a multiple of two. */
		c->width    = srcCodecCtx->width;
		c->height   = srcCodecCtx->height;
		
        /* timebase: This is the fundamental unit of time (in seconds) in terms
         * of which frame timestamps are represented. For fixed-fps content,
         * timebase should be 1/framerate and timestamp increments should be
         * identical to 1. */
		c->time_base.den = srcCodecCtx->time_base.den;
		c->time_base.num = srcCodecCtx->time_base.num;
		c->ticks_per_frame = srcCodecCtx->ticks_per_frame;
		//c->gop_size      = srcCodecCtx->gop_size;
		c->pix_fmt       = srcCodecCtx->pix_fmt;//AV_PIX_FMT_BGR32;
		//c->max_b_frames = 2;//srcCodecCtx->max_b_frames;


        //if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
        //    /* just for testing, we also add B frames */
        //    c->max_b_frames = 2;
        //}
        //if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
        //    /* Needed to avoid using macroblocks in which some coeffs overflow.
        //     * This does not happen with normal video, it just happens here as
        //     * the motion of the chroma plane does not match the luma plane. */
        //    c->mb_decision = 2;
        //}

    break;

    default:
        break;
    }

    /* Some formats want stream headers to be separate. */
    if (m_writeFmtCtx->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    return st;


}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::WriteAudioFrame(clMediaFrame& srcFrame)
{
    AVCodecContext *c;
    AVPacket pkt = { 0 }; // data and size must be 0;
	AVFrame *frame = av_frame_alloc();
    int got_packet, ret;

    av_init_packet(&pkt);
    c = m_outputAudioStream->codec;

	// mv todo not sure if this is correct
	int audioInputSize = c->frame_size;
	frame->nb_samples = audioInputSize;

	enum AVSampleFormat sampleFormat;
	av_opt_get_sample_fmt(m_SwrContext,"out_sample_fmt",0,&sampleFormat);

	ret = av_samples_alloc(m_audioDstData,NULL, av_frame_get_channels(m_frame), audioInputSize, sampleFormat, 1);

    ret = avcodec_fill_audio_frame(frame, c->channels, sampleFormat, (uint8_t *)m_audioDstData[0], audioInputSize * av_get_bytes_per_sample(sampleFormat) * c->channels, 1);
	if (ret < 0) {
		FF_TRACE("ERROR: filling audio frame data: %d\n", ret);
		return -1;
	}
	uint8_t* tempSrcArray[1];

	tempSrcArray[0]=srcFrame.buffer.get();
	ret = av_samples_copy(frame->data, tempSrcArray, 0,	0, frame->nb_samples, av_frame_get_channels(m_frame),sampleFormat);
	if (ret < 0) {
		FF_TRACE("ERROR: copying audio buffer for encode: %d\n", ret);
		return -1;
	}
	

    ret = avcodec_encode_audio2(c, &pkt, frame, &got_packet);
    if (ret < 0) {
        FF_TRACE("ERROR: encoding audio frame: %d\n", ret);
        return -1;
    }

    if (!got_packet)
        return 0;

	pkt.stream_index = m_outputAudioStream->index;

    /* Write the compressed frame to the media file. */

	//frame->pts = m_frame->pts;

    ret = av_interleaved_write_frame(m_writeFmtCtx, &pkt);
    if (ret != 0) {
        FF_TRACE("ERROR: While writing audio frame: %d\n", ret);
        //exit(1);
    }
	av_frame_free(&frame);
	av_freep(&m_audioDstData[0]); 

	//m_outputAudioPts += FindOutputAudioPtsPerFrame();
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE int clMediaFile::WriteVideoFrame(clMediaFrame& outFrame, float frameNumber, float startPosInSeconds, bool &frameWritten)
{
    int ret;
    AVCodecContext *c = m_outputVideoStream->codec;

	frameWritten = false;

	int gotPacket = 0;
    AVPacket pkt = { 0 };
        

    /* encode the image */
	av_free_packet(&pkt);
		
	av_init_packet(&pkt);
					
	if (m_pkt.dts != AV_NOPTS_VALUE)
		m_frame->pts = m_outputPts;
	else
		m_frame->pts = 0;

	double timeInSeconds =  (double)frameNumber * ( ((double)m_outputVideoStream->codec->time_base.num/(double)m_outputVideoStream->codec->time_base.den) * m_outputVideoStream->codec->ticks_per_frame);
	//m_sampleCallback((float)timeInSeconds + startPosInSeconds, outFrame.buffer,m_outputWidth* BYTES_PER_PIXEL, m_outputWidth, m_outputHeight);

	if(outFrame.size > 0)
	{
		uint8_t* tempArray[1];
		tempArray[0] = outFrame.buffer.get();
		int tempLineSize[AV_NUM_DATA_POINTERS];
		memset(tempLineSize,0,sizeof (tempLineSize));
		tempLineSize[0] = m_outputWidth * m_nBytesPerPixel;
		sws_scale(m_SWSContextToYUV, tempArray, tempLineSize, 0, m_videoDecCtx->height, m_frame->data, m_frame->linesize);
		ret = avcodec_encode_video2(c, &pkt, m_frame, &gotPacket);
	}
	else
	{
		// call with NULL to flush packets
		ret = avcodec_encode_video2(c, &pkt,NULL, &gotPacket);
	}

    if (ret < 0) 
	{
        FF_TRACE("ERROR: encoding video frame: %d with error: %d\n", (int)frameNumber, ret);
        return -1;
    }

    /* If size is zero, it means the image was buffered. */
    if (gotPacket && pkt.size) 
	{
		pkt.stream_index = m_videoStream->index;
		//pkt.pts = m_pkt.pts;
        /* Write the compressed frame to the media file. */
        ret = av_interleaved_write_frame(m_writeFmtCtx, &pkt);
		if (ret < 0) 
		{
			FF_TRACE("ERROR: writing video frame: %d with error %d\n", (int)frameNumber, ret);
			return -1;
		}
		frameWritten=true;
    } 
	m_outputPts += av_rescale_q(1, m_outputVideoStream->codec->time_base, m_outputVideoStream->time_base) * m_outputVideoStream->codec->ticks_per_frame;
		
	return 0;

}

//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
PRX_INTERFACE void clMediaFile::StopTranscode()
{
	m_isEOF = true;
}

PRX_INTERFACE void clMediaFile::SetAudioFormat(eAudioFormats format)
{
	if(format == kInteger16)
		av_opt_set_sample_fmt(m_SwrContext, "out_sample_fmt", AV_SAMPLE_FMT_S16,  0);
	else
		av_opt_set_sample_fmt(m_SwrContext, "out_sample_fmt", AV_SAMPLE_FMT_FLT,  0);

	m_audioFormat = format;

}

PRX_INTERFACE void clMediaFile::ConvertRGBToNV12(uint8_t* out, std::shared_ptr<const uint8_t> sharedIn,int width,int height)
{
	SwsContext* swsContextToYUV = sws_getContext(width, height, AV_PIX_FMT_BGR32, width, height, AV_PIX_FMT_NV12, SWS_POINT, 0, 0, 0);

	uint8_t* tempOutArray[2];
	tempOutArray[0] = out;
	tempOutArray[1] = out + (width*height);
	const uint8_t* tempInArray[1];
	tempInArray[0] = sharedIn.get();

	int tempInLineSize[AV_NUM_DATA_POINTERS];
	memset(tempInLineSize,0,sizeof (tempInLineSize));
	tempInLineSize[0] = width * 4;

	int tempOutLineSize[AV_NUM_DATA_POINTERS];
	memset(tempOutLineSize,0,sizeof (tempOutLineSize));
	tempOutLineSize[0] = width;
	tempOutLineSize[1] = width;

	sws_scale(swsContextToYUV, tempInArray, tempInLineSize, 0, height, tempOutArray, tempOutLineSize);
	//sws_scale(m_SWSContextYUV420PToYUV, m_frame->data, m_frame->linesize, 0, m_videoDecCtx->height, &tempArray[0], tempLineSize);
	sws_freeContext(swsContextToYUV);

}

PRX_INTERFACE void clMediaFile::ClearYuv2(uint8_t* out, int width,int height)
{
	SwsContext* swsContextToYUV = sws_getContext(width, height, AV_PIX_FMT_BGR32, width, height, AV_PIX_FMT_YUYV422, SWS_POINT, 0, 0, 0);
	FF_ASSERT(width<=TEMP_BUFFER_WIDTH);
	FF_ASSERT(height<=TEMP_BUFFER_HEIGHT);

	memset(m_tempBuffer,0,TEMP_BUFFER_WIDTH *TEMP_BUFFER_HEIGHT*4);
	uint8_t* tempOutArray[2];
	tempOutArray[0] = out;
	tempOutArray[1] = out + (width*height);
	const uint8_t* tempInArray[1];
	tempInArray[0] = m_tempBuffer;

	int tempInLineSize[AV_NUM_DATA_POINTERS];
	memset(tempInLineSize,0,sizeof (tempInLineSize));
	tempInLineSize[0] = width * 4;

	int tempOutLineSize[AV_NUM_DATA_POINTERS];
	memset(tempOutLineSize,0,sizeof (tempOutLineSize));
	tempOutLineSize[0] = width*2;
	//tempOutLineSize[1] = width;

	sws_scale(swsContextToYUV, tempInArray, tempInLineSize, 0, height, tempOutArray, tempOutLineSize);
	//sws_scale(m_SWSContextYUV420PToYUV, m_frame->data, m_frame->linesize, 0, m_videoDecCtx->height, &tempArray[0], tempLineSize);
	sws_freeContext(swsContextToYUV);

}
#if defined(WIN32)
static const WORD MAX_CONSOLE_LINES = 5000;
void clMediaFile::RedirectIOToConsole()
{

	int hConHandle;

	long lStdHandle;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;

	FILE *fp;
	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console

	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog

	// point to console as well
	std::ios_base::sync_with_stdio();

}
#endif
#if 0
//----------------------------------------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------------------------------------
AVStream * clMediaFile::AddStream(AVFormatContext *oc, AVCodec **codec, enum AVCodecID codec_id)
{
    AVCodecContext *c;
    AVStream *st;

    /* find the encoder */
    *codec = avcodec_find_encoder(codec_id);
    if (!(*codec)) {
        FF_TRACE("Could not find encoder for '%s'\n",
                avcodec_get_name(codec_id));
        exit(1);
    }

    st = avformat_new_stream(oc, *codec);
    if (!st) {
        FF_TRACE("Could not allocate stream\n");
        exit(1);
    }
    st->id = oc->nb_streams-1;
    c = st->codec;

    switch ((*codec)->type) {
    case AVMEDIA_TYPE_AUDIO:
        st->id = 1;
        c->sample_fmt  = AV_SAMPLE_FMT_S16;
        c->bit_rate    = 64000;
        c->sample_rate = 44100;
        c->channels    = 2;
        break;

    case AVMEDIA_TYPE_VIDEO:
        c->codec_id = codec_id;

        c->bit_rate = 400000;
        /* Resolution must be a multiple of two. */
        c->width    = 352;
        c->height   = 288;
        /* timebase: This is the fundamental unit of time (in seconds) in terms
         * of which frame timestamps are represented. For fixed-fps content,
         * timebase should be 1/framerate and timestamp increments should be
         * identical to 1. */
        c->time_base.den = STREAM_FRAME_RATE;
        c->time_base.num = 1;
        c->gop_size      = 12; /* emit one intra frame every twelve frames at most */
        c->pix_fmt       = STREAM_PIX_FMT;
        if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
            /* just for testing, we also add B frames */
            c->max_b_frames = 2;
        }
        if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
            /* Needed to avoid using macroblocks in which some coeffs overflow.
             * This does not happen with normal video, it just happens here as
             * the motion of the chroma plane does not match the luma plane. */
            c->mb_decision = 2;
        }
    break;

    default:
        break;
    }

    /* Some formats want stream headers to be separate. */
    if (oc->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    return st;
}


#endif

	