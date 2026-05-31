#pragma once

#include <SDL3/SDL_video.h>
#include <stddef.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

static_assert(sizeof(u8) == 1, "u8 must be equal to 1-byte");
static_assert(sizeof(u16) == 2, "u16 must be equal to 2-byte");
static_assert(sizeof(u32) == 4, "u32 must be equal to 4-byte");
static_assert(sizeof(u64) == 8, "u64 must be equal to 8-byte");

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

static_assert(sizeof(i8) == 1, "i8 must be equal to 1-byte");
static_assert(sizeof(i16) == 2, "i16 must be equal to 2-byte");
static_assert(sizeof(i32) == 4, "i32 must be equal to 4-byte");
static_assert(sizeof(i64) == 8, "i64 must be equal to 8-byte");

typedef float f32;
typedef double f64;

static_assert(sizeof(f32) == 4, "f32 must be equal to 4-byte");
static_assert(sizeof(f64) == 8, "f64 must be equal to 8-byte");

typedef const char *cstring;
static_assert(sizeof(cstring) == 8, "cstring must be equal to 8-byte");

#define FALSE 0
#define TRUE 1

#define WINDOW_RESIZABLE SDL_WINDOW_RESIZABLE
