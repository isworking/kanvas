#pragma once

#ifndef KVS_DRAWABLE_INTERNAL_H
#define KVS_DRAWABLE_INTERNAL_H

#include <kvs/drawable.h>

struct kvs_drawable
{
    kvs_sample_fn sample;
    kvs_destroy_fn destroy;
    kvs_clone_fn clone;
    kvs_bounds_fn bounds;

    kvs_drawable_state state;

    void *userdata;
};

#endif