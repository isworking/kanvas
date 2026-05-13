/* types.h */

#pragma once

#ifndef MRL_TYPES_H
#define MRL_TYPES_H

#ifdef __cplusplus
#define MRL_BEGIN_DECLS \
    extern "C"          \
    {
#define MRL_END_DECLS }
#else
#define MRL_BEGIN_DECLS
#define MRL_END_DECLS
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef MRL_BUILD_SHARED
#define MRL_API __declspec(dllexport)
#elif defined(MRL_USE_SHARED)
#define MRL_API __declspec(dllimport)
#else
#define MRL_API
#endif
#elif defined(__GNUC__) || defined(__clang__)
#define MRL_API __attribute__((visibility("default")))
#define MRL_INLINE static inline __attribute__((always_inline))
#define MRL_UNAVAILABLE(msg) __attribute__((error(msg)))
#else
#define MRL_API
#define MRL_INLINE static inline
#define MRL_UNAVAILABLE(msg)
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

MRL_BEGIN_DECLS

#define MRL_POS(x, y) \
    (mrl_pos) { x, y }
#define MRL_SIZE(w, h) \
    (mrl_size) { w, h }
#define MRL_RECT(x, y, w, h) \
    (mrl_rect) { x, y, w, h }

#define MRL_DATA(drawable, kind) \
    ((mrl_##kind##_data *)(mrl_drawable_get_userdata(drawable)))

#define MRL_USERDATA(drawable, type) \
    ((type *)mrl_drawable_get_userdata(drawable))

typedef uint8_t mrl_u8;
typedef uint32_t mrl_u32;
typedef int32_t mrl_i32;

typedef struct mrl_pos
{
    int x;
    int y;
} mrl_pos;

typedef struct mrl_size
{
    int w;
    int h;
} mrl_size;

typedef struct mrl_rect
{
    int x;
    int y;
    int w;
    int h;
} mrl_rect;

MRL_END_DECLS

#endif