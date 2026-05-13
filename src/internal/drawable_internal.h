#pragma once

#ifndef MRL_DRAWABLE_INTERNAL_H
#define MRL_DRAWABLE_INTERNAL_H

#include <mrl/drawable.h>

struct mrl_drawable
{
    mrl_sample_fn sample;
    mrl_destroy_fn destroy;
    mrl_clone_fn clone;
    mrl_bounds_fn bounds;

    mrl_drawable_state state;

    void *userdata;
};

#endif