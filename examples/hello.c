#include <kvs/kvs.h>

int main(void)
{
    kvs_canvas *canvas = kvs_canvas_create(KVS_SIZE(800, 600));

    kvs_drawable *rect = kvs_drawable_rect(KVS_SIZE(200, 100));

    kvs_drawable_set_color(rect, kvs_color_from_rgba(255, 0, 0, 128));
    kvs_canvas_add(canvas, rect, KVS_POS(100, 100));

    kvs_drawable_set_color(rect, kvs_color_from_rgba(0, 255, 0, 128));
    kvs_canvas_add(canvas, rect, KVS_POS(200, 150));

    kvs_drawable_set_color(rect, kvs_color_from_rgba(0, 255, 255, 128));
    kvs_canvas_add(canvas, rect, KVS_POS(200, 150));

    kvs_canvas_render(canvas);

    kvs_image *out = kvs_canvas_export_to_image(canvas);
    kvs_image_write_png(out, "build/output.png");
    kvs_image_destroy(out);

    kvs_canvas_destroy(canvas);

    kvs_drawable_destroy(rect);

    return 0;
}