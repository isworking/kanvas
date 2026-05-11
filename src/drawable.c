#include <kvs/drawable.h>
#include <kvs/types.h>

#include "internal/drawable_internal.h"

kvs_drawable *kvs_drawable_create(kvs_sample_fn sample, kvs_destroy_fn destroy, kvs_clone_fn clone)
{
    kvs_drawable *drawable = malloc(sizeof(kvs_drawable));

    if (!drawable)
    {
        return NULL;
    }

    drawable->sample = sample;
    drawable->destroy = destroy;
    drawable->clone = clone;

    kvs_drawable_set_state(drawable, (kvs_drawable_state){0});
    kvs_drawable_set_userdata(drawable, NULL);

    return drawable;
}

void kvs_drawable_set_state(kvs_drawable *drawable, kvs_drawable_state state)
{
    drawable->state = state;
}

kvs_drawable_state kvs_drawable_get_state(const kvs_drawable *drawable)
{
    return drawable->state;
}

void kvs_drawable_set_color(kvs_drawable *drawable, kvs_color color)
{
    drawable->state.color = color;
}

kvs_color kvs_drawable_get_color(const kvs_drawable *drawable)
{
    return drawable->state.color;
}

void kvs_drawable_set_userdata(kvs_drawable *drawable, void *userdata)
{
    drawable->userdata = userdata;
}

void *kvs_drawable_get_userdata(const kvs_drawable *drawable)
{
    return drawable->userdata;
}

bool kvs_drawable_sample(kvs_drawable *drawable, kvs_canvas *canvas, kvs_pos position, kvs_color *out)
{
    return drawable->sample(canvas, kvs_drawable_get_state(drawable), kvs_drawable_get_userdata(drawable), position, out);
}

void kvs_drawable_destroy(kvs_drawable *drawable)
{
    if (!drawable)
        return;

    drawable->destroy(kvs_drawable_get_userdata(drawable));
    free(drawable);
}

kvs_drawable *kvs_drawable_clone(const kvs_drawable *src)
{
    return src->clone(src);
}