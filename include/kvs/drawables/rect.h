/* drawables/rect.h */

#pragma once

#ifndef KVS_DRAWABLES_RECT_H
#define KVS_DRAWABLES_RECT_H

#include <kvs/types.h>

KVS_BEGIN_DECLS

typedef struct kvs_drawable kvs_drawable;

KVS_API kvs_drawable *kvs_drawable_rect(kvs_size size);

KVS_API void kvs_drawable_rect_set_size(kvs_drawable *drawable, kvs_size size);
KVS_API kvs_size kvs_drawable_rect_get_size(kvs_drawable *drawable);

KVS_API void kvs_drawable_rect_set_width(kvs_drawable *drawable, int width);
KVS_API int kvs_drawable_rect_get_width(kvs_drawable *drawable);

KVS_API void kvs_drawable_rect_set_height(kvs_drawable *drawable, int height);
KVS_API int kvs_drawable_rect_get_height(kvs_drawable *drawable);

KVS_END_DECLS

#endif