#include <kvs/canvas.h>
#include <kvs/image.h>

#include "internal/canvas_internal.h"

#include <stdlib.h>
#include <string.h>

kvs_canvas_node *kvs_canvas_node_create(kvs_drawable *drawable)
{
    kvs_canvas_node *node = malloc(sizeof(kvs_canvas_node));

    kvs_canvas_node_set_drawable_clone(node, drawable);

    kvs_canvas_node_set_next(node, NULL);

    kvs_canvas_node_set_visible(node, true);
    kvs_canvas_node_set_opacity(node, 1.0f);

    return node;
}

void kvs_canvas_node_set_drawable_clone(kvs_canvas_node *node, kvs_drawable *drawable)
{
    node->drawable = kvs_drawable_clone(drawable);
}

kvs_drawable *kvs_canvas_node_get_drawable(const kvs_canvas_node *node)
{
    return node->drawable;
}

void kvs_canvas_node_set_visible(kvs_canvas_node *node, bool visible)
{
    node->visible = visible;
}

bool kvs_canvas_node_get_visible(const kvs_canvas_node *node)
{
    return node->visible;
}

void kvs_canvas_node_set_opacity(kvs_canvas_node *node, float opacity)
{
    node->opacity = opacity;
}

float kvs_canvas_node_get_opacity(const kvs_canvas_node *node)
{
    return node->opacity;
}

void kvs_canvas_node_set_position(kvs_canvas_node *node, kvs_pos position)
{
    node->position = position;
}

kvs_pos kvs_canvas_node_get_position(const kvs_canvas_node *node)
{
    return node->position;
}

void kvs_canvas_node_set_next(kvs_canvas_node *node, kvs_canvas_node *next)
{
    node->next = next;
}

kvs_canvas_node *kvs_canvas_node_get_next(const kvs_canvas_node *node)
{
    return node->next;
}

kvs_canvas *kvs_canvas_create(kvs_size size)
{
    kvs_canvas *canvas = malloc(sizeof(kvs_canvas));

    if (!canvas)
        return NULL;

    canvas->size = size;

    canvas->pixels = malloc(sizeof(kvs_color) * size.w * size.h);

    if (!canvas->pixels)
    {
        free(canvas);
        return NULL;
    }

    memset(canvas->pixels, 0,
           sizeof(kvs_color) * size.w * size.h);

    canvas->head = NULL;
    canvas->tail = NULL;

    return canvas;
}

kvs_canvas *kvs_canvas_create_from_image(
    kvs_image *img)
{
    if (!img)
        return NULL;

    kvs_canvas *canvas =
        kvs_canvas_create(
            kvs_image_get_size(img));

    if (!canvas)
        return NULL;

    size_t total =
        (size_t)kvs_image_get_width(img) *
        (size_t)kvs_image_get_height(img);

    memcpy(
        canvas->pixels,
        kvs_image_get_pixels(img),
        total * sizeof(*canvas->pixels));

    return canvas;
}

kvs_size kvs_canvas_get_size(const kvs_canvas *canvas)
{
    return canvas->size;
}

int kvs_canvas_get_width(const kvs_canvas *canvas)
{
    return kvs_canvas_get_size(canvas).w;
}

int kvs_canvas_get_height(const kvs_canvas *canvas)
{
    return kvs_canvas_get_size(canvas).h;
}

kvs_color *kvs_canvas_get_pixels(const kvs_canvas *canvas)
{
    return canvas->pixels;
}

void kvs_canvas_set_pixel_blend(kvs_canvas *canvas, kvs_pos position, kvs_color color)
{
    kvs_canvas_get_pixels(canvas)[position.y * canvas->size.w + position.x] = kvs_color_blend(color, kvs_canvas_get_pixels(canvas)[position.y * canvas->size.w + position.x]);
}

kvs_color kvs_canvas_get_pixel(const kvs_canvas *canvas, kvs_pos position)
{
    return kvs_canvas_get_pixels(canvas)[position.y * canvas->size.w + position.x];
}

void kvs_canvas_set_head(kvs_canvas *canvas, kvs_canvas_node *node)
{
    canvas->head = node;
}

kvs_canvas_node *kvs_canvas_get_head(const kvs_canvas *canvas)
{
    return canvas->head;
}

void kvs_canvas_set_tail(kvs_canvas *canvas, kvs_canvas_node *node)
{
    canvas->tail = node;
}

kvs_canvas_node *kvs_canvas_get_tail(const kvs_canvas *canvas)
{
    return canvas->tail;
}

void kvs_canvas_destroy(kvs_canvas *canvas)
{
    kvs_canvas_node *current = canvas->head;

    while (current)
    {
        kvs_drawable_destroy(current->drawable);

        kvs_canvas_node *next = current->next;
        if (canvas != NULL)
            free(current);

        current = next;
    }

    canvas->head = NULL;
    canvas->tail = NULL;

    if (!canvas)
        return;

    free(canvas->pixels);
    free(canvas);
}

kvs_canvas_node *kvs_canvas_add(
    kvs_canvas *canvas,
    kvs_drawable *drawable, kvs_pos position)
{
    if (!canvas || !drawable)
        return NULL;

    kvs_canvas_node *node = kvs_canvas_node_create(drawable);

    if (!node)
        return NULL;

    kvs_canvas_node_set_position(node, position);

    if (!kvs_canvas_get_head(canvas) || !kvs_canvas_get_tail(canvas))
    {
        kvs_canvas_set_head(canvas, node);
        kvs_canvas_set_tail(canvas, node);
        return node;
    }

    kvs_canvas_node_set_next(kvs_canvas_get_tail(canvas), node);
    kvs_canvas_set_tail(canvas, kvs_canvas_node_get_next(kvs_canvas_get_tail(canvas)));

    return node;
}

void kvs_canvas_render(kvs_canvas *canvas)
{
    kvs_color *pixels = kvs_canvas_get_pixels(canvas);

    for (int y = 0; y < kvs_canvas_get_height(canvas); y++)
    {
        for (int x = 0; x < kvs_canvas_get_width(canvas); x++)
        {
            int idx = y * kvs_canvas_get_width(canvas) + x;

            kvs_canvas_node *current_node = kvs_canvas_get_head(canvas);

            while (current_node)
            {
                if (kvs_canvas_node_get_visible(current_node))
                {
                    kvs_pos position = kvs_canvas_node_get_position(current_node);

                    int local_y = y - position.y;
                    int local_x = x - position.x;

                    kvs_pos local_pos = KVS_POS(local_x, local_y);

                    kvs_color out;

                    kvs_drawable *drawable = kvs_canvas_node_get_drawable(current_node);

                    if (kvs_drawable_sample(drawable, canvas, local_pos, &out))
                    {
                        out.a = (kvs_u8)((float)out.a * kvs_canvas_node_get_opacity(current_node));

                        pixels[idx] = kvs_color_blend(out, pixels[idx]);
                    }
                }

                current_node = kvs_canvas_node_get_next(current_node);
            }
        }
    }
}

void kvs_canvas_clear(
    kvs_canvas *canvas,
    kvs_color color)
{
    if (!canvas)
        return;

    kvs_color *pixels = kvs_canvas_get_pixels(canvas);

    if (!pixels)
        return;

    size_t total =
        (size_t)canvas->size.w *
        (size_t)canvas->size.h;

    for (size_t i = 0; i < total; i++)
        pixels[i] = color;
}

kvs_image *kvs_canvas_export_to_image(
    kvs_canvas *canvas)
{
    if (!canvas)
        return NULL;

    kvs_image *img = kvs_image_create(canvas->size);

    if (!img)
        return NULL;

    kvs_image_set_pixels_copy(img, canvas->pixels);

    return img;
}