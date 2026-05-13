#pragma once

#ifndef MRL_IMAGE_INTERNAL_H
#define MRL_IMAGE_INTERNAL_H

#include <mrl/image.h>

struct mrl_image
{
    mrl_size size;

    mrl_color *pixels;
};

#endif