#pragma once

#ifndef MRL_CANVAS_INTERNAL_H
#define MRL_CANVAS_INTERNAL_H

#include <mrl/canvas.h>
#include <mrl/drawable.h>

typedef struct mrl_canvas_node
{
    mrl_drawable *drawable;

    bool visible;
    float opacity;
    mrl_rect bounds;

    struct mrl_canvas_node *next;
} mrl_canvas_node;

struct mrl_canvas
{
    mrl_size size;

    mrl_color *pixels;

    mrl_canvas_node *head;
    mrl_canvas_node *tail;
};

#endif