/* drawables/rect.h */

#pragma once

#ifndef MRL_DRAWABLES_RECT_H
#define MRL_DRAWABLES_RECT_H

#include <mrl/types.h>

MRL_BEGIN_DECLS

typedef struct mrl_drawable mrl_drawable;

MRL_API mrl_drawable *mrl_drawable_rect(mrl_size size);

MRL_API void mrl_drawable_rect_set_size(mrl_drawable *drawable, mrl_size size);
MRL_API mrl_size mrl_drawable_rect_get_size(const mrl_drawable *drawable);

MRL_API void mrl_drawable_rect_set_width(mrl_drawable *drawable, int width);
MRL_API int mrl_drawable_rect_get_width(const mrl_drawable *drawable);

MRL_API void mrl_drawable_rect_set_height(mrl_drawable *drawable, int height);
MRL_API int mrl_drawable_rect_get_height(const mrl_drawable *drawable);

MRL_END_DECLS

#endif