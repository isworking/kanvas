/* color.h */

#pragma once

#ifndef MRL_COLOR_H
#define MRL_COLOR_H

#include <mrl/types.h>

MRL_BEGIN_DECLS

typedef struct mrl_color
{
    mrl_u8 r;
    mrl_u8 g;
    mrl_u8 b;
    mrl_u8 a;
} mrl_color;

_Static_assert(
    sizeof(mrl_color) == 4,
    "mrl_color must be 4 bytes");

MRL_API mrl_color mrl_color_from_rgba(
    mrl_u8 r,
    mrl_u8 g,
    mrl_u8 b,
    mrl_u8 a);

MRL_API mrl_color mrl_color_from_rgb(
    mrl_u8 r,
    mrl_u8 g,
    mrl_u8 b);

MRL_API mrl_color mrl_color_from_hex_rgb(mrl_u32 hex);

MRL_API mrl_color mrl_color_from_hex_rgba(mrl_u32 hex);

MRL_API mrl_color mrl_color_blend(mrl_color src, mrl_color dst);

MRL_END_DECLS

#endif