#pragma once

#ifndef KVS_CANVAS_INTERNAL_H
#define KVS_CANVAS_INTERNAL_H

#include <kvs/canvas.h>
#include <kvs/drawable.h>

typedef struct kvs_canvas_node
{
    kvs_drawable *drawable;

    bool visible;
    float opacity;
    kvs_rect bounds;

    struct kvs_canvas_node *next;
} kvs_canvas_node;

struct kvs_canvas
{
    kvs_size size;

    kvs_color *pixels;

    kvs_canvas_node *head;
    kvs_canvas_node *tail;
};

#endif