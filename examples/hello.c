#include <mrl/mrl.h>

int main(void)
{
    mrl_canvas *canvas = mrl_canvas_create(MRL_SIZE(800, 600));

    mrl_drawable *rect = mrl_drawable_rect(MRL_SIZE(200, 100));

    mrl_drawable_set_color(rect, mrl_color_from_hex_rgba(0xFF000080));
    mrl_canvas_add(canvas, rect, MRL_POS(100, 100));

    mrl_drawable_set_color(rect, mrl_color_from_hex_rgba(0x00FF0080));
    mrl_canvas_add(canvas, rect, MRL_POS(200, 150));

    mrl_drawable_set_color(rect, mrl_color_from_hex_rgba(0x00FFFF80));
    mrl_canvas_add(canvas, rect, MRL_POS(225, 175));

    mrl_canvas_render(canvas);

    mrl_image *out = mrl_canvas_export_to_image(canvas);
    mrl_image_write_png(out, "examples/output.png");
    mrl_image_destroy(out);

    mrl_canvas_destroy(canvas);

    mrl_drawable_destroy(rect);

    return 0;
}