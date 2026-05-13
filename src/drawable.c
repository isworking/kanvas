#include <mrl/drawable.h>
#include <mrl/types.h>

#include "internal/drawable_internal.h"

#include <stdlib.h>

mrl_drawable *mrl_drawable_create(mrl_sample_fn sample, mrl_destroy_fn destroy, mrl_clone_fn clone, mrl_bounds_fn bounds)
{
    mrl_drawable *drawable = malloc(sizeof(mrl_drawable));

    if (!drawable)
    {
        return NULL;
    }

    drawable->sample = sample;
    drawable->destroy = destroy;
    drawable->clone = clone;
    drawable->bounds = bounds;

    mrl_drawable_set_state(drawable, (mrl_drawable_state){0});
    mrl_drawable_set_userdata(drawable, NULL);

    return drawable;
}

void mrl_drawable_set_state(mrl_drawable *drawable, mrl_drawable_state state)
{
    drawable->state = state;
}

mrl_drawable_state mrl_drawable_get_state(const mrl_drawable *drawable)
{
    return drawable->state;
}

void mrl_drawable_set_color(mrl_drawable *drawable, mrl_color color)
{
    drawable->state.color = color;
}

mrl_color mrl_drawable_get_color(const mrl_drawable *drawable)
{
    return drawable->state.color;
}

void mrl_drawable_set_userdata(mrl_drawable *drawable, void *userdata)
{
    drawable->userdata = userdata;
}

void *mrl_drawable_get_userdata(const mrl_drawable *drawable)
{
    return drawable->userdata;
}

bool mrl_drawable_sample(mrl_drawable *drawable, mrl_canvas *canvas, mrl_pos position, mrl_color *out)
{
    return drawable->sample(canvas, mrl_drawable_get_state(drawable), mrl_drawable_get_userdata(drawable), position, out);
}

void mrl_drawable_destroy(mrl_drawable *drawable)
{
    if (!drawable)
        return;

    drawable->destroy(mrl_drawable_get_userdata(drawable));
    free(drawable);
}

mrl_drawable *mrl_drawable_clone(const mrl_drawable *src)
{
    return src->clone(src);
}

mrl_rect mrl_drawable_bounds(
    const mrl_drawable *drawable,
    mrl_pos position)
{
    return drawable->bounds(drawable, position);
}