#include <kvs/types.h>
#include <kvs/drawable.h>

#include <kvs/drawables/image.h>

typedef struct kvs_image_data
{
    kvs_image *src;
} kvs_image_data;

static bool kvs_drawable_image_sample(kvs_canvas *canvas, kvs_drawable_state state, void *userdata, kvs_pos position, kvs_color *out)
{
    (void)state;

    kvs_image_data *img = userdata;

    int img_width = kvs_image_get_width(img->src);
    int img_height = kvs_image_get_height(img->src);

    (void)canvas;

    if (
        position.x < 0 ||
        position.y < 0 ||
        position.x >= img_width ||
        position.y >= img_height)
        return false;

    *out = kvs_image_get_pixel(img->src, position);

    return true;
}

static void kvs_drawable_image_destroy(
    void *userdata)
{
    if (!userdata)
        return;

    free(userdata);
}

static kvs_drawable *kvs_drawable_image_clone(
    const kvs_drawable *src)
{
    kvs_drawable *copy =
        kvs_drawable_create(kvs_drawable_image_sample, kvs_drawable_image_destroy, kvs_drawable_image_clone);

    if (!copy)
        return NULL;

    kvs_image_data *src_data =
        kvs_drawable_get_userdata(src);

    kvs_image_data *data =
        malloc(sizeof(kvs_image_data));

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

kvs_drawable *kvs_drawable_image(kvs_image *src)
{
    kvs_drawable *drawable = kvs_drawable_create(kvs_drawable_image_sample, kvs_drawable_image_destroy, kvs_drawable_image_clone);

    if (!drawable)
    {
        return NULL;
    }

    kvs_image_data *data = malloc(sizeof(kvs_image_data));

    if (!data)
    {
        free(drawable);
        return NULL;
    }

    data->src = src;

    kvs_drawable_state state;

    state.color = kvs_color_from_rgba(0, 0, 0, 0);

    kvs_drawable_set_userdata(drawable, data);
    kvs_drawable_set_state(drawable, state);

    return drawable;
}

void kvs_drawable_image_set_source(kvs_drawable *drawable, kvs_image *src)
{
    KVS_DATA(drawable, image)->src = src;
}

kvs_image *kvs_drawable_image_get_source(const kvs_drawable *drawable)
{
    return KVS_DATA(drawable, image)->src;
}