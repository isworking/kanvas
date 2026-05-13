#include <mrl/types.h>
#include <mrl/drawable.h>

#include <mrl/drawables/rect.h>

#include <stdlib.h>

typedef struct mrl_rect_data
{
    mrl_size size;
} mrl_rect_data;

mrl_rect mrl_rect_bounds(const mrl_drawable *drawable, mrl_pos position);

static bool mrl_rect_sample(mrl_canvas *canvas, mrl_drawable_state state, void *userdata, mrl_pos position, mrl_color *out)
{

    (void)canvas;
    (void)userdata;

    if (position.x < 0 || position.y < 0)
        return false;

    *out = state.color;

    return true;
}

static void mrl_rect_destroy(
    void *userdata)
{
    if (!userdata)
        return;

    free(userdata);
}

static mrl_drawable *mrl_rect_clone(
    const mrl_drawable *src)
{
    mrl_drawable *copy =
        mrl_drawable_create(mrl_rect_sample, mrl_rect_destroy, mrl_rect_clone, mrl_rect_bounds);

    if (!copy)
        return NULL;

    mrl_rect_data *src_data =
        mrl_drawable_get_userdata(src);

    mrl_rect_data *data =
        malloc(sizeof(mrl_rect_data));

    if (!data)
    {
        free(copy);
        return NULL;
    }

    *data = *src_data;

    mrl_drawable_set_state(copy, mrl_drawable_get_state(src));
    mrl_drawable_set_userdata(copy, data);

    return copy;
}

mrl_rect mrl_rect_bounds(const mrl_drawable *drawable, mrl_pos position)
{
    return MRL_RECT(position.x, position.y, mrl_drawable_rect_get_width(drawable), mrl_drawable_rect_get_height(drawable));
}

mrl_drawable *mrl_drawable_rect(mrl_size size)
{
    mrl_drawable *drawable = mrl_drawable_create(mrl_rect_sample, mrl_rect_destroy, mrl_rect_clone, mrl_rect_bounds);

    if (!drawable)
    {
        return NULL;
    }

    mrl_rect_data *data = malloc(sizeof(mrl_rect_data));

    if (!data)
    {
        free(drawable);
        return NULL;
    }

    data->size = size;

    mrl_drawable_state state;

    state.color = mrl_color_from_rgba(255, 255, 255, 255);

    mrl_drawable_set_userdata(drawable, data);
    mrl_drawable_set_state(drawable, state);

    return drawable;
}

void mrl_drawable_rect_set_size(mrl_drawable *drawable, mrl_size size)
{
    MRL_DATA(drawable, rect)->size = size;
}
mrl_size mrl_drawable_rect_get_size(const mrl_drawable *drawable)
{
    return MRL_DATA(drawable, rect)->size;
}

void mrl_drawable_rect_set_width(mrl_drawable *drawable, int width)
{
    MRL_DATA(drawable, rect)->size.w = width;
}

int mrl_drawable_rect_get_width(const mrl_drawable *drawable)
{
    return MRL_DATA(drawable, rect)->size.w;
}

void mrl_drawable_rect_set_height(mrl_drawable *drawable, int height)
{
    MRL_DATA(drawable, rect)->size.h = height;
}

int mrl_drawable_rect_get_height(const mrl_drawable *drawable)
{
    return MRL_DATA(drawable, rect)->size.h;
}