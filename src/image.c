#include <kvs/image.h>

#include "internal/image_internal.h"

kvs_image *kvs_image_create(kvs_size size)
{
    size_t total =
        (size_t)size.w *
        (size_t)size.h;

    kvs_image *img = malloc(sizeof(*img));

    if (!img)
        return NULL;

    img->size = size;

    img->pixels =
        malloc(total * sizeof(*img->pixels));

    if (!img->pixels)
    {
        free(img);
        return NULL;
    }

    return img;
}

kvs_size kvs_image_get_size(const kvs_image *img)
{
    return img->size;
}

int kvs_image_get_width(const kvs_image *img)
{
    return kvs_image_get_size(img).w;
}

int kvs_image_get_height(const kvs_image *img)
{
    return kvs_image_get_size(img).h;
}

kvs_color *kvs_image_get_pixels(const kvs_image *img)
{
    return img->pixels;
}

kvs_color kvs_image_get_pixel(const kvs_image *img, kvs_pos position)
{
    int idx = position.y * kvs_image_get_width(img) + position.x;

    return kvs_image_get_pixels(img)[idx];
}

void kvs_image_set_pixels_copy(kvs_image *img, kvs_color *pixels)
{
    size_t total =
        (size_t)img->size.w *
        (size_t)img->size.h;

    memcpy(
        kvs_image_get_pixels(img),
        pixels,
        total * sizeof(*pixels));
}

void kvs_image_destroy(kvs_image *img)
{
    if (!img)
        return;

    free(kvs_image_get_pixels(img));
    free(img);
}