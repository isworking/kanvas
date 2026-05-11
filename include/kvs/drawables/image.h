/* drawables/image.h */

#pragma once

#ifndef KVS_DRAWABLES_IMAGE_H
#define KVS_DRAWABLES_IMAGE_H

#include <kvs/types.h>
#include <kvs/image.h>

KVS_BEGIN_DECLS

typedef struct kvs_drawable kvs_drawable;

KVS_API kvs_drawable *kvs_drawable_image(kvs_image *src);

KVS_API void kvs_drawable_image_set_source(kvs_drawable *drawable, kvs_image *src);
KVS_API kvs_image *kvs_drawable_image_get_source(const kvs_drawable *drawable);

KVS_END_DECLS

#endif