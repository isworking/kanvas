/* drawables/image.h */

#pragma once

#ifndef MRL_DRAWABLES_IMAGE_H
#define MRL_DRAWABLES_IMAGE_H

#include <mrl/types.h>
#include <mrl/image.h>

MRL_BEGIN_DECLS

typedef struct mrl_drawable mrl_drawable;

MRL_API mrl_drawable *mrl_drawable_image(mrl_image *src);

MRL_API void mrl_drawable_image_set_source(mrl_drawable *drawable, mrl_image *src);
MRL_API mrl_image *mrl_drawable_image_get_source(const mrl_drawable *drawable);

MRL_END_DECLS

#endif