# Kanvas

A lightweight 2D raster graphics and canvas library written in C.

> [!WARNING]
> Kanvas is under active development. The API is unstable and may change without notice.

## Features

- Image-backed canvases
- Drawable primitives
- Alpha compositing
- PNG and PPM import/export
- Retained-mode rendering

## Example

```c
#include <kvs/kvs.h>

int main(void)
{
    kvs_canvas *canvas = kvs_canvas_create(KVS_SIZE(800, 600));

    kvs_drawable *rect = kvs_drawable_rect(KVS_SIZE(200, 100));

    kvs_drawable_set_color(rect, kvs_color_from_hex_rgba(0xFF000080));
    kvs_canvas_add(canvas, rect, KVS_POS(100, 100));

    kvs_drawable_set_color(rect, kvs_color_from_hex_rgba(0x00FF0080));
    kvs_canvas_add(canvas, rect, KVS_POS(200, 150));

    kvs_drawable_set_color(rect, kvs_color_from_hex_rgba(0x00FFFF80));
    kvs_canvas_add(canvas, rect, KVS_POS(225, 175));

    kvs_canvas_render(canvas);

    kvs_image *out = kvs_canvas_export_to_image(canvas);
    kvs_image_write_png(out, "output.png");
    kvs_image_destroy(out);

    kvs_canvas_destroy(canvas);

    kvs_drawable_destroy(rect);

    return 0;
}
```

This should result in the following image:
![Kanvas screenshot](examples/output.png)

See [examples/](examples/) for more.

## Dependencies

- `libpng` (optional, disable with `KVS_ENABLE_PNG=OFF`)

## Build

```sh
make
```

Or manually with CMake:

```sh
cmake -B build -S .
cmake --build build
```

## Status

Early development. The API is unstable and tests are still being written.

## Roadmap

- [x] ~~Image drawables~~
    - [ ] Use `state.color` as tint
- [x] ~~Color format support~~
    - [x] ~~RGBA~~
    - [x] ~~RGB~~
    - [x] ~~Hexadecimal~~
- [x] ~~Drawable bounding boxes~~
- [ ] Rasterize per drawable instead of per pixel
- [ ] Error handling
- [ ] Add tests
- [ ] Add color constants
- [ ] Improve documentation and examples
- [ ] Image format support
    - [x] ~~PNG~~
        - [ ] Add more detailed PNG metadata
    - [ ] JPEG
- [ ] Drawable scaling
- [ ] Text drawables
    - [ ] `FreeType` integration
    - [ ] `HarfBuzz` shaping
- [ ] Boolean drawable operations

## License

Licensed under the Apache License 2.0.  
See [LICENSE](LICENSE).