/* date = December 7th 2021 9:56 pm */

#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdint.h>

#define internal static

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef int32_t b32;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

typedef size_t memory_index;

typedef float f32;
typedef double f64;

typedef uintptr_t umm;
typedef intptr_t smm;

typedef b32 b32x;
typedef u32 u32x;

#define LOG_ERR(...) fprintf(stderr,  __VA_ARGS__)
#define LOG(...) fprintf(stdout,  __VA_ARGS__)

#ifdef ENABLE_ASSERT
#define ASSERT(condition, ...) if(!(condition)) {LOG_ERR(__VA_ARGS__); *((u32*)0) = 0;}
#else 
#define ASSERT(condition, ...)
#endif

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

#endif //BASE_H
