/* color.h */

#pragma once

#ifndef KVS_COLOR_H
#define KVS_COLOR_H

#include <kvs/types.h>

KVS_BEGIN_DECLS

typedef struct kvs_color
{
    kvs_u8 r;
    kvs_u8 g;
    kvs_u8 b;
    kvs_u8 a;
} kvs_color;

_Static_assert(
    sizeof(kvs_color) == 4,
    "kvs_color must be 4 bytes");

KVS_API kvs_color kvs_color_from_rgba(
    kvs_u8 r,
    kvs_u8 g,
    kvs_u8 b,
    kvs_u8 a);

KVS_API kvs_color kvs_color_from_rgb(
    kvs_u8 r,
    kvs_u8 g,
    kvs_u8 b);

KVS_API kvs_color kvs_color_from_hex_rgb(kvs_u32 hex);

KVS_API kvs_color kvs_color_from_hex_rgba(kvs_u32 hex);

KVS_API kvs_color kvs_color_blend(kvs_color src, kvs_color dst);

KVS_END_DECLS

#endif