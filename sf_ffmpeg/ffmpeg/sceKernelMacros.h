#pragma once

//#define open sceKernelOpen
#define nanosleep sceKernelNanosleep
#define unlink sceKernelUnlink
#define read sceKernelRead
#define write sceKernelWrite
#define close sceKernelClose
#define fstat sceKernelFstat
#define stat sceKernelStat
#define mkdir sceKernelMkdir
#define rmdir sceKernelRmdir
#define rename sceKernelRename
//#define mmap sceKernelMmap
#define lseek sceKernelLseek
#define munmap sceKernelMunmap
#define pthread_mutex_lock scePthreadMutexLock
#define pthread_mutex_unlock scePthreadMutexUnlock



