#include <sys/time.h>
#include <kernel.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>


int	gettimeofday(struct timeval *ltv, struct timezone *tz)
{
	SceKernelTimeval tv;
	int ret = sceKernelGettimeofday(&tv);

	ltv->tv_sec = tv.tv_sec;
	ltv->tv_usec = tv.tv_usec;

	return ret; 
}

int	open(const char *path, int mode, ...)
{
	return sceKernelOpen(path,mode,0);
}

void *	 mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void *res;
	sceKernelMmap(addr,len,prot,flags,fd,offset,&res);
	return res;
}

/*
int nanosleep(const struct timespec *ts0, struct timespec *ts1)
{
	SceKernelTimespec reqTs;
	SceKernelTimespec retTs;

	reqTs.tv_nsec = ts0->tv_nsec;
	reqTs.tv_sec = ts0->tv_sec;
	int ret = sceKernelNanosleep(&reqTs, &retTs);

	ts1->tv_nsec = retTs.tv_nsec;
	ts1->tv_sec = retTs.tv_sec;

	return ret;
	
}

int	 unlink(const char *s)
{
	return sceKernelUnlink(s);
}

ssize_t	 read(int d, void *buf, size_t nbytes)
{
	return sceKernelRead(d,buf,nbytes);
}

ssize_t	 write(int d, const void *buf, size_t nbytes)
{
	return sceKernelWrite(d,buf,nbytes);
}

int	 close(int d)
{
	return sceKernelClose(d);
}

int	fstat(int d, struct stat *s)
{
	return sceKernelFstat(d,s);
}

int stat(const char* path, struct stat *sb)
{
	return sceKernelStat(path,sb);
}

int	mkdir(const char *path, mode_t mode)
{
	return sceKernelMkdir(path, mode);
}

int	 rmdir(const char *path)
{
	return sceKernelRmdir(path);
}

int rename(const char *from, const char *to)
{
	return sceKernelRename(from,to);
}


off_t lseek(int fildes, off_t offset, int whence)
{
	return sceKernelLseek(fildes,offset,whence);
}

int	munmap(void *addr, size_t len)
{
	return sceKernelMunmap(addr,len);
}
*/
char *tempnam(const char *dir, const char *pfx)
{
	// mv todo implement this correctly
	size_t len = strlen(pfx);
	char* s = malloc(4+len);
	s[0]='t';
	s[1]='m';
	s[2]='p';
	s[3]='.';

	return s;

}

int	mprotect(const void *b, size_t s, int d)
{
	return sceKernelMprotect(b,s,d);
}
