#include <mrl/image.h>

#include "internal/image_internal.h"

#include <stdlib.h>
#include <string.h>

mrl_image *mrl_image_create(mrl_size size)
{
    size_t total =
        (size_t)size.w *
        (size_t)size.h;

    mrl_image *img = malloc(sizeof(*img));

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

mrl_size mrl_image_get_size(const mrl_image *img)
{
    return img->size;
}

int mrl_image_get_width(const mrl_image *img)
{
    return mrl_image_get_size(img).w;
}

int mrl_image_get_height(const mrl_image *img)
{
    return mrl_image_get_size(img).h;
}

mrl_color *mrl_image_get_pixels(const mrl_image *img)
{
    return img->pixels;
}

mrl_color mrl_image_get_pixel(const mrl_image *img, mrl_pos position)
{
    int idx = position.y * mrl_image_get_width(img) + position.x;

    return mrl_image_get_pixels(img)[idx];
}

void mrl_image_set_pixels_copy(mrl_image *img, mrl_color *pixels)
{
    size_t total =
        (size_t)img->size.w *
        (size_t)img->size.h;

    memcpy(
        mrl_image_get_pixels(img),
        pixels,
        total * sizeof(*pixels));
}

void mrl_image_destroy(mrl_image *img)
{
    if (!img)
        return;

    free(mrl_image_get_pixels(img));
    free(img);
}