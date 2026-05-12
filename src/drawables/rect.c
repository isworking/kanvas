#include <kvs/types.h>
#include <kvs/drawable.h>

#include <kvs/drawables/rect.h>

#include <stdlib.h>

typedef struct kvs_rect_data
{
    kvs_size size;
} kvs_rect_data;

kvs_rect kvs_rect_bounds(const kvs_drawable *drawable, kvs_pos position);

static bool kvs_rect_sample(kvs_canvas *canvas, kvs_drawable_state state, void *userdata, kvs_pos position, kvs_color *out)
{

    (void)canvas;
    (void)userdata;

    if (position.x < 0 || position.y < 0)
        return false;

    *out = state.color;

    return true;
}

static void kvs_rect_destroy(
    void *userdata)
{
    if (!userdata)
        return;

    free(userdata);
}

static kvs_drawable *kvs_rect_clone(
    const kvs_drawable *src)
{
    kvs_drawable *copy =
        kvs_drawable_create(kvs_rect_sample, kvs_rect_destroy, kvs_rect_clone, kvs_rect_bounds);

    if (!copy)
        return NULL;

    kvs_rect_data *src_data =
        kvs_drawable_get_userdata(src);

    kvs_rect_data *data =
        malloc(sizeof(kvs_rect_data));

    if (!data)
    {
        free(copy);
        return NULL;
    }

    *data = *src_data;

    kvs_drawable_set_state(copy, kvs_drawable_get_state(src));
    kvs_drawable_set_userdata(copy, data);

    return copy;
}

kvs_rect kvs_rect_bounds(const kvs_drawable *drawable, kvs_pos position)
{
    return KVS_RECT(position.x, position.y, kvs_drawable_rect_get_width(drawable), kvs_drawable_rect_get_height(drawable));
}

kvs_drawable *kvs_drawable_rect(kvs_size size)
{
    kvs_drawable *drawable = kvs_drawable_create(kvs_rect_sample, kvs_rect_destroy, kvs_rect_clone, kvs_rect_bounds);

    if (!drawable)
    {
        return NULL;
    }

    kvs_rect_data *data = malloc(sizeof(kvs_rect_data));

    if (!data)
    {
        free(drawable);
        return NULL;
    }

    data->size = size;

    kvs_drawable_state state;

    state.color = kvs_color_from_rgba(255, 255, 255, 255);

    kvs_drawable_set_userdata(drawable, data);
    kvs_drawable_set_state(drawable, state);

    return drawable;
}

void kvs_drawable_rect_set_size(kvs_drawable *drawable, kvs_size size)
{
    KVS_DATA(drawable, rect)->size = size;
}
kvs_size kvs_drawable_rect_get_size(const kvs_drawable *drawable)
{
    return KVS_DATA(drawable, rect)->size;
}

void kvs_drawable_rect_set_width(kvs_drawable *drawable, int width)
{
    KVS_DATA(drawable, rect)->size.w = width;
}

int kvs_drawable_rect_get_width(const kvs_drawable *drawable)
{
    return KVS_DATA(drawable, rect)->size.w;
}

void kvs_drawable_rect_set_height(kvs_drawable *drawable, int height)
{
    KVS_DATA(drawable, rect)->size.h = height;
}

int kvs_drawable_rect_get_height(const kvs_drawable *drawable)
{
    return KVS_DATA(drawable, rect)->size.h;
}