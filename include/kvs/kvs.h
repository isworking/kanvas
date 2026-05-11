/* kvs.h */

#pragma once

#ifndef KVS_H
#define KVS_H

#define KVS_VERSION_MAJOR 0
#define KVS_VERSION_MINOR 0
#define KVS_VERSION_PATCH 1

#define KVS_VERSION              \
    ((KVS_VERSION_MAJOR << 16) | \
     (KVS_VERSION_MINOR << 8) |  \
     KVS_VERSION_PATCH)

#define KVS_VERSION_STRING "0.0.1"

#include <kvs/canvas.h>
#include <kvs/color.h>
#include <kvs/drawable.h>
#include <kvs/image.h>
#include <kvs/types.h>

#endif