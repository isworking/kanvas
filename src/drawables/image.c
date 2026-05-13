#include <mrl/types.h>
#include <mrl/drawable.h>

#include <mrl/drawables/image.h>

#include <stdlib.h>

typedef struct mrl_image_data
{
    mrl_image *src;
} mrl_image_data;

mrl_rect mrl_drawable_image_bounds(const mrl_drawable *drawable, mrl_pos position);

static bool mrl_drawable_image_sample(mrl_canvas *canvas, mrl_drawable_state state, void *userdata, mrl_pos position, mrl_color *out)
{
    (void)state;
    (void)canvas;

    mrl_image_data *img = userdata;

    if (position.x < 0 || position.y < 0)
        return false;

    *out = mrl_image_get_pixel(img->src, position);

    return true;
}

static void mrl_drawable_image_destroy(
    void *userdata)
{
    if (!userdata)
        return;

    free(userdata);
}

static mrl_drawable *mrl_drawable_image_clone(
    const mrl_drawable *src)
{
    mrl_drawable *copy =
        mrl_drawable_create(mrl_drawable_image_sample, mrl_drawable_image_destroy, mrl_drawable_image_clone, mrl_drawable_image_bounds);

    if (!copy)
        return NULL;
    mrl_rect mrl_drawable_image_bounds(const mrl_drawable *drawable, mrl_pos position);
    mrl_image_data *src_data =
        mrl_drawable_get_userdata(src);

    mrl_image_data *data =
        malloc(sizeof(mrl_image_data));

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

mrl_rect mrl_drawable_image_bounds(const mrl_drawable *drawable, mrl_pos position)
{
    mrl_image *img = mrl_drawable_image_get_source(drawable);

    int img_width = mrl_image_get_width(img);
    int img_height = mrl_image_get_height(img);

    return MRL_RECT(position.x, position.y, img_width, img_height);
}

mrl_drawable *mrl_drawable_image(mrl_image *src)
{
    mrl_drawable *drawable = mrl_drawable_create(mrl_drawable_image_sample, mrl_drawable_image_destroy, mrl_drawable_image_clone, mrl_drawable_image_bounds);

    if (!drawable)
    {
        return NULL;
    }

    mrl_image_data *data = malloc(sizeof(mrl_image_data));

    if (!data)
    {
        free(drawable);
        return NULL;
    }

    data->src = src;

    mrl_drawable_state state;

    state.color = mrl_color_from_rgba(0, 0, 0, 0);

    mrl_drawable_set_userdata(drawable, data);
    mrl_drawable_set_state(drawable, state);

    return drawable;
}

void mrl_drawable_image_set_source(mrl_drawable *drawable, mrl_image *src)
{
    MRL_DATA(drawable, image)->src = src;
}

mrl_image *mrl_drawable_image_get_source(const mrl_drawable *drawable)
{
    return MRL_DATA(drawable, image)->src;
}