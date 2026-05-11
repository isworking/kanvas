#pragma once

#ifndef KVS_IMAGE_INTERNAL_H
#define KVS_IMAGE_INTERNAL_H

#include <kvs/image.h>

struct kvs_image
{
    kvs_size size;

    kvs_color *pixels;
};

#endif