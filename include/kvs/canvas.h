/* canvas.h */

#pragma once

#ifndef KVS_CANVAS_H
#define KVS_CANVAS_H

#include <kvs/types.h>
#include <kvs/color.h>
#include <kvs/image.h>

KVS_BEGIN_DECLS

typedef struct kvs_canvas kvs_canvas;
typedef struct kvs_canvas_node kvs_canvas_node;
typedef struct kvs_drawable kvs_drawable;

KVS_API kvs_canvas_node *kvs_canvas_node_create(kvs_drawable *drawable);

KVS_API void kvs_canvas_node_set_drawable_clone(kvs_canvas_node *node, kvs_drawable *drawable);
KVS_API kvs_drawable *kvs_canvas_node_get_drawable(const kvs_canvas_node *node);

KVS_API void kvs_canvas_node_set_visible(kvs_canvas_node *node, bool visible);
KVS_API bool kvs_canvas_node_get_visible(const kvs_canvas_node *node);

KVS_API void kvs_canvas_node_set_opacity(kvs_canvas_node *node, float opacity);
KVS_API float kvs_canvas_node_get_opacity(const kvs_canvas_node *node);

KVS_API void kvs_canvas_node_set_bounds(kvs_canvas_node *node, kvs_rect bounds);
KVS_API kvs_rect kvs_canvas_node_get_bounds(const kvs_canvas_node *node);

KVS_API void kvs_canvas_node_set_position(kvs_canvas_node *node, kvs_pos position);
KVS_API kvs_pos kvs_canvas_node_get_position(const kvs_canvas_node *node);

KVS_API void kvs_canvas_node_set_next(kvs_canvas_node *node, kvs_canvas_node *next);
KVS_API kvs_canvas_node *kvs_canvas_node_get_next(const kvs_canvas_node *node);

KVS_API kvs_canvas *kvs_canvas_create(kvs_size size);
KVS_API kvs_canvas *kvs_canvas_create_from_image(kvs_image *image);

KVS_API kvs_size kvs_canvas_get_size(const kvs_canvas *canvas);
KVS_API int kvs_canvas_get_width(const kvs_canvas *canvas);
KVS_API int kvs_canvas_get_height(const kvs_canvas *canvas);

KVS_API kvs_color *kvs_canvas_get_pixels(const kvs_canvas *canvas);
KVS_API void kvs_canvas_set_pixel_blend(kvs_canvas *canvas, kvs_pos position, kvs_color color);
KVS_API kvs_color kvs_canvas_get_pixel(const kvs_canvas *canvas, kvs_pos position);

KVS_API void kvs_canvas_set_head(kvs_canvas *canvas, kvs_canvas_node *node);
KVS_API kvs_canvas_node *kvs_canvas_get_head(const kvs_canvas *canvas);

KVS_API void kvs_canvas_set_tail(kvs_canvas *canvas, kvs_canvas_node *node);
KVS_API kvs_canvas_node *kvs_canvas_get_tail(const kvs_canvas *canvas);

KVS_API void kvs_canvas_destroy(kvs_canvas *canvas);

KVS_API kvs_canvas_node *kvs_canvas_add(
    kvs_canvas *canvas,
    kvs_drawable *drawable,
    kvs_pos position);

KVS_API void kvs_canvas_render(
    kvs_canvas *canvas);

KVS_API void kvs_canvas_clear(
    kvs_canvas *canvas,
    kvs_color color);

KVS_API kvs_image *kvs_canvas_export_to_image(kvs_canvas *canvas);

KVS_END_DECLS

#endif