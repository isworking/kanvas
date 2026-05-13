/* drawable.h */

#pragma once

#ifndef MRL_DRAWABLE_H
#define MRL_DRAWABLE_H

#include <mrl/types.h>
#include <mrl/color.h>

#include <mrl/drawables/rect.h>
#include <mrl/drawables/image.h>

MRL_BEGIN_DECLS

typedef struct mrl_drawable mrl_drawable;
typedef struct mrl_canvas mrl_canvas;

typedef struct mrl_drawable_state
{
    mrl_color color;
} mrl_drawable_state;

typedef bool (*mrl_sample_fn)(
    mrl_canvas *canvas,
    mrl_drawable_state state,
    void *userdata,
    mrl_pos position,
    mrl_color *out);

typedef void (*mrl_destroy_fn)(
    void *userdata);

typedef mrl_drawable *(*mrl_clone_fn)(
    const mrl_drawable *src);

typedef mrl_rect (*mrl_bounds_fn)(
    const mrl_drawable *drawable,
    mrl_pos position);

MRL_API mrl_drawable *mrl_drawable_create(
    mrl_sample_fn sample,
    mrl_destroy_fn destroy,
    mrl_clone_fn clone,
    mrl_bounds_fn bounds);

MRL_API void mrl_drawable_set_state(
    mrl_drawable *drawable,
    mrl_drawable_state state);
MRL_API mrl_drawable_state mrl_drawable_get_state(const mrl_drawable *drawable);

MRL_API void mrl_drawable_set_color(
    mrl_drawable *drawable,
    mrl_color color);
MRL_API mrl_color mrl_drawable_get_color(const mrl_drawable *drawable);

MRL_API void mrl_drawable_set_userdata(
    mrl_drawable *drawable,
    void *userdata);
MRL_API void *mrl_drawable_get_userdata(const mrl_drawable *drawable);

MRL_API bool mrl_drawable_sample(
    mrl_drawable *drawable,
    mrl_canvas *canvas,
    mrl_pos position,
    mrl_color *out);

MRL_API void mrl_drawable_destroy(
    mrl_drawable *drawable);

MRL_API mrl_drawable *mrl_drawable_clone(
    const mrl_drawable *src);

MRL_API mrl_rect mrl_drawable_bounds(
    const mrl_drawable *drawable,
    mrl_pos position);

MRL_END_DECLS

#endif