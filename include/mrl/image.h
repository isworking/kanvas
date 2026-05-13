/* image.h */

#pragma once

#ifndef MRL_IMAGE_H
#define MRL_IMAGE_H

#include <mrl/types.h>
#include <mrl/color.h>

#include <mrl/config.h>

MRL_BEGIN_DECLS

typedef struct mrl_image mrl_image;

MRL_API mrl_image *mrl_image_create(mrl_size size);

MRL_API mrl_size mrl_image_get_size(const mrl_image *img);

MRL_API int mrl_image_get_width(const mrl_image *img);
MRL_API int mrl_image_get_height(const mrl_image *img);

MRL_API mrl_color *mrl_image_get_pixels(const mrl_image *img);
MRL_API mrl_color mrl_image_get_pixel(const mrl_image *img, mrl_pos position);
MRL_API void mrl_image_set_pixels_copy(mrl_image *img, mrl_color *pixels);

MRL_API void mrl_image_destroy(mrl_image *img);

MRL_API bool mrl_image_write_ppm(
    const mrl_image *img,
    const char *path);
mrl_image *mrl_image_read_ppm(const char *path);

#if MRL_ENABLE_PNG

MRL_API bool mrl_image_write_png(
    const mrl_image *img,
    const char *path);
MRL_API mrl_image *mrl_image_read_png(const char *path);

#else

MRL_UNAVAILABLE(
    "Mural was built without PNG support "
    "(enable MRL_WITH_PNG)")
bool mrl_image_write_png(
    const mrl_image *image,
    const char *path);

MRL_UNAVAILABLE(
    "Mural was built without PNG support "
    "(enable MRL_WITH_PNG)")
mrl_image *mrl_image_read_png(const char *path);

#endif

MRL_END_DECLS

#endif