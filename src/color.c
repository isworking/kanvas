#include <mrl/color.h>

mrl_color mrl_color_from_rgba(mrl_u8 r,
                              mrl_u8 g,
                              mrl_u8 b,
                              mrl_u8 a)
{
    return (mrl_color){
        .r = r,
        .g = g,
        .b = b,
        .a = a};
}

mrl_color mrl_color_from_rgb(
    mrl_u8 r,
    mrl_u8 g,
    mrl_u8 b)
{
    return (mrl_color){
        .r = r,
        .g = g,
        .b = b,
        .a = 255};
}

mrl_color mrl_color_from_hex_rgb(mrl_u32 hex)
{
    return mrl_color_from_rgba(
        (hex >> 16) & 0xFF,
        (hex >> 8) & 0xFF,
        hex & 0xFF,
        255);
}

mrl_color mrl_color_from_hex_rgba(mrl_u32 hex)
{
    return mrl_color_from_rgba(
        (hex >> 24) & 0xFF,
        (hex >> 16) & 0xFF,
        (hex >> 8) & 0xFF,
        hex & 0xFF);
}

mrl_color mrl_color_blend(mrl_color src, mrl_color dst)
{
    float srcA = src.a / 255.0f;
    float dstA = dst.a / 255.0f;

    float outA = srcA + dstA * (1.0f - srcA);

    if (outA <= 0.0f)
    {
        return (mrl_color){0, 0, 0, 0};
    }

    mrl_color out;

    out.r = (mrl_u8)(((src.r * srcA) + (dst.r * dstA * (1.0f - srcA))) / outA);

    out.g = (mrl_u8)(((src.g * srcA) + (dst.g * dstA * (1.0f - srcA))) / outA);

    out.b = (mrl_u8)(((src.b * srcA) + (dst.b * dstA * (1.0f - srcA))) / outA);

    out.a = (mrl_u8)(outA * 255.0f);

    return out;
}