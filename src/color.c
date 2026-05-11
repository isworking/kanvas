#include <kvs/color.h>

kvs_color kvs_color_from_rgba(kvs_u8 r,
                              kvs_u8 g,
                              kvs_u8 b,
                              kvs_u8 a)
{
    return (kvs_color){
        .r = r,
        .g = g,
        .b = b,
        .a = a};
}

static inline kvs_u8 kvs_color_blend_channel(
    kvs_u8 src,
    kvs_u8 dst,
    kvs_u8 alpha)
{
    return (src * alpha + dst * (255 - alpha)) / 255;
}

kvs_color kvs_color_blend(kvs_color src, kvs_color dst)
{
    float srcA = src.a / 255.0f;
    float dstA = dst.a / 255.0f;

    float outA = srcA + dstA * (1.0f - srcA);

    if (outA <= 0.0f)
    {
        return (kvs_color){0, 0, 0, 0};
    }

    kvs_color out;

    out.r = (kvs_u8)(((src.r * srcA) + (dst.r * dstA * (1.0f - srcA))) / outA);

    out.g = (kvs_u8)(((src.g * srcA) + (dst.g * dstA * (1.0f - srcA))) / outA);

    out.b = (kvs_u8)(((src.b * srcA) + (dst.b * dstA * (1.0f - srcA))) / outA);

    out.a = (kvs_u8)(outA * 255.0f);

    return out;
}