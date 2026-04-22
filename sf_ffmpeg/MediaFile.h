#pragma once
#ifdef LIBRARY_IMPL
#define PRX_INTERFACE __declspec(dllexport)
#else
#define PRX_INTERFACE __declspec(dllimport)
#endif

#include <stdarg.h>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <Common.h>
#include <Thread.h>

#define FF_TRACE(msg, ...)				NM_TRACE(NM_MEDIA, msg, ##__VA_ARGS__)
#define FF_ASSERTMSG(test, msg, ...)	NM_ASSERTMSG(test, msg, ##__VA_ARGS__)
#define FF_ASSERT(test) NM_ASSERT(test)

#define VIDEO_THREAD_COUNT 5
#define AUDIO_THREAD_COUNT 5

#define TEMP_BUFFER_WIDTH 1280
#define TEMP_BUFFER_HEIGHT 800
extern "C" 
{

    #include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include "libswscale/swscale.h"
	#include "libswresample/swresample.h"
	//int avformat_open_input(AVFormatContext **ps, const char *filename, AVInputFormat *fmt, AVDictionary **options);
}
typedef  int (*tSampleCallbackFuncPtr)(float seconds, void* data, unsigned int stride, unsigned int width, unsigned int height);
class clMediaFile
{
public:
	enum eFrameType
	{
		AUDIO_FRAME_TYPE,
		VIDEO_FRAME_TYPE,
		OTHER_FRAME_TYPE,
	};

	enum eAudioFormats
	{
		kInteger16,
		kSameAsSource,
	};

	enum eOpenStream
	{
		kVideoStream = 0x1,
		kAudioStream = 0x2,
	};

	struct clMediaFrame
	{
		clMediaFrame(): type(OTHER_FRAME_TYPE),buffer(NULL), size(0),width(0),height(0),timeStampInMS(0),framePts(0) {}
		eFrameType type;
		std::shared_ptr<uint8_t> buffer;
		int size;
		int width;
		int height;
		int64_t timeStampInMS;
		int64_t framePts;

		clMediaFrame& operator = (const clMediaFrame& frame)
		{
			this->type = frame.type;
			this->buffer = frame.buffer;
			this->width = frame.width;
			this->height = frame.height;
			this->size = frame.size;
			this->timeStampInMS = frame.timeStampInMS;
			this->framePts = frame.framePts;
			return *this;
		}

		bool operator < (const clMediaFrame& frame)
		{
			return this->framePts < frame.framePts;
		}

	};
public:
	PRX_INTERFACE static void InitializeFFMpeg();
	PRX_INTERFACE clMediaFile();
	PRX_INTERFACE ~clMediaFile();
	PRX_INTERFACE int ConvertVideoPtsToMS(int64_t pts);
	PRX_INTERFACE int ConvertAudioPtsToMS(int64_t pts);
	PRX_INTERFACE int64_t ConvertSecondsToVideoPts( float seekPosInSeconds );
	PRX_INTERFACE int64_t ConvertSecondsToAudioPts( float seekPosInSeconds );
	//int ConvertMSToPTS(int64_t pts);
	PRX_INTERFACE int Open(const char* filename, int streamFlags);
	//int OpenAudioOnly(const char* filename);
	//int OpenVideoOnly(const char* filename);
	PRX_INTERFACE void Close();
	PRX_INTERFACE void SetOutputSize(int width, int height);
	PRX_INTERFACE void GetNextFrame(clMediaFrame& outFrame);
	PRX_INTERFACE void GetNextVideoFrame(clMediaFrame& outFrame);
	PRX_INTERFACE void GetNextAudioFrame(clMediaFrame& outFrame);
	PRX_INTERFACE static void FreeFrame(clMediaFrame& frame);
	PRX_INTERFACE uint8_t* getNextVideoFrame();
	PRX_INTERFACE uint8_t* getNextAudioFrame();

	// Seek to the exact start of the clip. This is potentially slow
	PRX_INTERFACE clMediaFrame Seek(float seekPosInSeconds);

	PRX_INTERFACE void SeekToAudioFrame(float seekPosInSeconds);

	PRX_INTERFACE clMediaFrame SeekToClosestKeyFrame(float seekPosInSeconds);

	PRX_INTERFACE float GetDurationInSeconds();
	PRX_INTERFACE float GetAudioDurationInSeconds();
	PRX_INTERFACE int GetBufferSize();
	PRX_INTERFACE static bool GenerateThumbnails(const char* filename, 
		                           float startPosInSeconds, 
								   float timeBetweenSamplesInSeconds, 
								   int thumbCount, 
								   int width, 
								   int height,
								   std::vector<uint8_t*>& aThumbs);
	PRX_INTERFACE int GetAudioSampleRate();
	PRX_INTERFACE int GetAudioNumChannels();
	PRX_INTERFACE int GetAudioSampleCount();
	PRX_INTERFACE bool GetIsEOF();
	PRX_INTERFACE bool GetIsOpen() {return m_opened;}

	// File name including full path
	PRX_INTERFACE const std::string& GetFilename() { return m_filename; }

	PRX_INTERFACE int Transcode(const char* filename,double startPosInSeconds, double endPosInSeconds);
	//! @TODO: FIX THIS HACK
	PRX_INTERFACE void StartTranscode()
	{
		m_isEOF = false;
	}
	PRX_INTERFACE void StopTranscode();
	//cb(seconds, IntPtr(pSrc),stride,m_sampleWidth,m_sampleHeight);
	PRX_INTERFACE void SetSampleCallback(tSampleCallbackFuncPtr cb) {m_sampleCallback = cb;}
	
	PRX_INTERFACE bool GetHasAudio(){return m_bHasAudio;};
	PRX_INTERFACE void SetAudioFormat(eAudioFormats format);
	PRX_INTERFACE int GetCurrentVideoTimestamp();
	PRX_INTERFACE int GetCurrentAudioTimestamp();
	PRX_INTERFACE int GetMillisecondsPerVideoFrame(){return ConvertVideoPtsToMS(FindPtsPerFrame());}
	PRX_INTERFACE int GetFirstFrameTimestamp(){return ConvertVideoPtsToMS(m_minPts);}
	PRX_INTERFACE void SetDecodeToRGB(bool useRGB){ m_bConvertToRgb = useRGB;}

	PRX_INTERFACE static void ConvertRGBToNV12(uint8_t* out, std::shared_ptr<const uint8_t> sharedIn,int width,int height);
	PRX_INTERFACE static void ClearYuv2(uint8_t* out, int w, int h);
	PRX_INTERFACE void SetThreadCounts(int video, int audio) {m_nVideoThreadCount = video; m_nAudioThreadCount = audio;};

	/*! @brief A mutex for preventing multi-threaded access to the media file open. Only one thread at a time can call av_open2() */
	static nmThread::clCriticalSectionSimple& GetCriticalSection()  {return m_criticalSectionMediaFile;}
	static void InitializeCriticalSection(){m_criticalSectionMediaFile.Initialize();};
	static void TerminateCriticalSection(){m_criticalSectionMediaFile.Terminate();};
private:
	clMediaFrame SeekFrameByFrame(int64_t pts);
	void SeekBackwards( int64_t desiredFrameNumber);
	int DecodePacket(int *got_frame, int cached, clMediaFrame& outFrame);
	int DecodeAudioPacket(int *got_frame, int cached,clMediaFrame& outFrame);
	int DecodeVideoPacket(int *got_frame, int cached,clMediaFrame& outFrame);
	int OpenCodecContext(int *stream_idx, enum AVMediaType type, int threadCount);
	void RedirectIOToConsole();
	int SetupWriter(const char* srcPath, int width, int height);
	AVStream *AddStream(AVStream* srcStream, AVCodec *destCodec);
	int WriteAudioFrame(clMediaFrame& frame);
	int WriteVideoFrame(clMediaFrame& frame, float frameNumber, float startPosInSeconds, bool& frameWritten);
	int GetNextFrameInternal(clMediaFrame& outFrame);
	int GetNextAudioFrameInternal(clMediaFrame& frame);
	int GetNextVideoFrameInternal(clMediaFrame& frame);
	void CloseVideo();
	void CloseAudio();
	int64_t FindPtsPerFrame();
	int64_t FindOutputVideoPtsPerFrame();
	int64_t FindOutputAudioPtsPerFrame();

private:

	tSampleCallbackFuncPtr m_sampleCallback;
	// source 
	AVFormatContext* m_fmtCtx;
	AVCodec* m_videoCodec;
	AVCodec* m_audioCodec;
	AVStream *m_videoStream; 
	AVStream *m_audioStream;
	AVCodecContext *m_videoDecCtx;
	AVCodecContext *m_audioDecCtx;
	AVFrame *m_frame;
	AVFrame *m_pOutputFrame;
	AVPacket m_pkt;
	int64_t	m_inputPts;
	int64_t m_inputDts;

	//dst
	AVFormatContext* m_writeFmtCtx;
	AVOutputFormat* m_outputFormat;
	AVStream *m_outputVideoStream;
	AVStream *m_outputAudioStream;
	int64_t			m_outputPts;

	SwsContext* m_SWSContextToRGB;
	SwsContext* m_SWSContextYUV420PToYUV;
	SwsContext* m_SWSContextToYUV;
	SwrContext* m_SwrContext;

	int				m_videoDstLinesize[4];
	uint8_t**		m_audioDstData;
	AVSampleFormat	m_audioDstFmt;
	//uint16_t*		m_audioDstData;
	int				m_audioDstLinesize;
	int				m_audioDstBufSize;
	int				m_videoStreamIdx;
	int				m_audioStreamIdx;
	int				m_videoFrameCount;
	std::string		m_filename;
	unsigned int	m_outputWidth;
	unsigned int	m_outputHeight;
	bool			m_isEOF;
	bool			m_opened;
	int64_t			m_currentPts;
	int64_t			m_currentAudioPts;
	bool			m_bHasAudio;
	eAudioFormats	m_audioFormat;
	int64_t			m_minPts;
	bool			m_bConvertToRgb;
	int				m_nBytesPerPixel;
	int				m_nVideoThreadCount;
	int				m_nAudioThreadCount;
	static uint8_t	m_tempBuffer[TEMP_BUFFER_WIDTH*TEMP_BUFFER_HEIGHT*4];

	// A mutex for preventing multi-threaded access to the media file open
	// only one thread at a time can call av_open2()
	PRX_INTERFACE static nmThread::clCriticalSectionSimple m_criticalSectionMediaFile;

};