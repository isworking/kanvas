/* color.h */

#pragma once

#ifndef KVS_COLOR_H
#define KVS_COLOR_H

#include <kvs/types.h>

KVS_BEGIN_DECLS

typedef struct
{
    kvs_u8 r;
    kvs_u8 g;
    kvs_u8 b;
    kvs_u8 a;
} kvs_color;

KVS_API kvs_color kvs_color_from_rgba(
    kvs_u8 r,
    kvs_u8 g,
    kvs_u8 b,
    kvs_u8 a);

KVS_API kvs_color kvs_color_blend(kvs_color src, kvs_color dst);

KVS_END_DECLS

#endif