/* image.h */

#pragma once

#ifndef KVS_IMAGE_H
#define KVS_IMAGE_H

#include <kvs/types.h>
#include <kvs/color.h>

KVS_BEGIN_DECLS

typedef struct kvs_image kvs_image;

KVS_API kvs_image *kvs_image_create(kvs_size size);

KVS_API kvs_size kvs_image_get_size(kvs_image *img);
KVS_API int kvs_image_get_width(kvs_image *img);
KVS_API int kvs_image_get_height(kvs_image *img);

KVS_API kvs_color *kvs_image_get_pixels(kvs_image *img);
KVS_API void kvs_image_set_pixels_copy(kvs_image *img, kvs_color *pixels);

KVS_API void kvs_image_destroy(kvs_image *img);

KVS_API bool kvs_image_write_ppm(
    kvs_image *img,
    const char *path);
kvs_image *kvs_image_read_ppm(const char *path);

KVS_API bool kvs_image_write_png(
    kvs_image *img,
    const char *path);
kvs_image *kvs_image_read_png(const char *path);

KVS_END_DECLS

#endif