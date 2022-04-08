#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>


typedef double real_t;
typedef double rtime_t;
typedef char * string_t;

// SIMD alignment macros
#define ALIGN_64 __attribute__((aligned(64)))
#define ALIGN_32 __attribute__((aligned(32)))
#define ALIGN_16 __attribute__((aligned(16)))

double timestamp(void);
string_t markerName(string_t baseName, int n);
int isPot2 (int n);

#endif // __UTILS_H__

