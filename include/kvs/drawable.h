/* drawable.h */

#pragma once

#ifndef KVS_DRAWABLE_H
#define KVS_DRAWABLE_H

#include <kvs/types.h>
#include <kvs/color.h>

#include <kvs/drawables/rect.h>
#include <kvs/drawables/image.h>

KVS_BEGIN_DECLS

typedef struct kvs_drawable kvs_drawable;
typedef struct kvs_canvas kvs_canvas;

typedef struct kvs_drawable_state
{
    kvs_color color;
} kvs_drawable_state;

typedef bool (*kvs_sample_fn)(
    kvs_canvas *canvas,
    kvs_drawable_state state,
    void *userdata,
    kvs_pos position,
    kvs_color *out);

typedef void (*kvs_destroy_fn)(
    void *userdata);

typedef kvs_drawable *(*kvs_clone_fn)(
    const kvs_drawable *src);

KVS_API kvs_drawable *kvs_drawable_create(
    kvs_sample_fn sample,
    kvs_destroy_fn destroy,
    kvs_clone_fn clone);

KVS_API void kvs_drawable_set_state(
    kvs_drawable *drawable,
    kvs_drawable_state state);

KVS_API kvs_drawable_state kvs_drawable_get_state(
    kvs_drawable *drawable);

KVS_API void kvs_drawable_set_color(
    kvs_drawable *drawable,
    kvs_color color);

KVS_API kvs_color kvs_drawable_get_color(
    kvs_drawable *drawable);

KVS_API void kvs_drawable_set_userdata(
    kvs_drawable *drawable,
    void *userdata);

KVS_API void *kvs_drawable_get_userdata(
    kvs_drawable *drawable);

KVS_API bool kvs_drawable_sample(
    kvs_drawable *drawable,
    kvs_canvas *canvas,
    kvs_pos position,
    kvs_color *out);

KVS_API void kvs_drawable_destroy(
    kvs_drawable *drawable);

KVS_API kvs_drawable *kvs_drawable_clone(
    const kvs_drawable *src);

KVS_END_DECLS

#endif