/* types.h */

#pragma once

#ifndef KVS_TYPES_H
#define KVS_TYPES_H

#ifdef __cplusplus
#define KVS_BEGIN_DECLS \
    extern "C"          \
    {
#define KVS_END_DECLS }
#else
#define KVS_BEGIN_DECLS
#define KVS_END_DECLS
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef KVS_BUILD_SHARED
#define KVS_API __declspec(dllexport)
#elif defined(KVS_USE_SHARED)
#define KVS_API __declspec(dllimport)
#else
#define KVS_API
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define KVS_API __attribute__((visibility("default")))
#define KVS_INLINE static inline __attribute__((always_inline))
#else
#define KVS_API
#define KVS_INLINE static inline
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

KVS_BEGIN_DECLS

#define KVS_POS(x, y) \
    (kvs_pos) { x, y }
#define KVS_SIZE(w, h) \
    (kvs_size) { w, h }
#define KVS_RECT(x, y, w, h) \
    (kvs_rect) { x, y, w, h }

#define KVS_DATA(drawable, kind) \
    ((kvs_##kind##_data *)(kvs_drawable_get_userdata(drawable)))

typedef uint8_t kvs_u8;
typedef uint32_t kvs_u32;
typedef int32_t kvs_i32;

typedef struct kvs_pos
{
    int x;
    int y;
} kvs_pos;

typedef struct kvs_size
{
    int w;
    int h;
} kvs_size;

typedef struct kvs_rect
{
    int x;
    int y;
    int w;
    int h;
} kvs_rect;

KVS_END_DECLS

#endif