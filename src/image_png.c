#include <kvs/image.h>

#include <png.h>

bool kvs_image_write_png(kvs_image *img, const char *path)
{
    FILE *fp = fopen(path, "wb");

    if (!fp)
    {
        return false;
    }

    int img_width = kvs_image_get_width(img);
    int img_height = kvs_image_get_height(img);

    png_structp png = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        NULL,
        NULL,
        NULL);

    png_infop info = png_create_info_struct(png);

    if (setjmp(png_jmpbuf(png)))
    {
        png_destroy_write_struct(
            &png,
            &info);

        fclose(fp);

        return false;
    }

    png_init_io(png, fp);

    png_set_IHDR(
        png,
        info,
        img_width,
        img_height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);

    png_bytep *rows =
        malloc(sizeof(png_bytep) * img_height);

    for (int y = 0; y < img_height; y++)
    {
        rows[y] =
            (png_bytep)(kvs_image_get_pixels(img) +
                        y * img_width);
    }

    png_write_image(png, rows);
    png_write_end(png, NULL);

    free(rows);

    png_destroy_write_struct(
        &png,
        &info);

    fclose(fp);

    return true;
}

kvs_image *kvs_image_read_png(const char *path)
{
    FILE *fp = fopen(path, "rb");

    if (!fp)
    {
        return NULL;
    }

    png_structp png =
        png_create_read_struct(
            PNG_LIBPNG_VER_STRING,
            NULL,
            NULL,
            NULL);

    if (!png)
    {
        fclose(fp);
        return NULL;
    }

    png_infop info =
        png_create_info_struct(png);

    if (!info)
    {
        png_destroy_read_struct(
            &png,
            NULL,
            NULL);

        fclose(fp);

        return NULL;
    }

    if (setjmp(png_jmpbuf(png)))
    {
        png_destroy_read_struct(
            &png,
            &info,
            NULL);

        fclose(fp);

        return NULL;
    }

    png_init_io(png, fp);

    png_read_info(png, info);

    int width =
        png_get_image_width(png, info);

    int height =
        png_get_image_height(png, info);

    png_byte color_type =
        png_get_color_type(png, info);

    png_byte bit_depth =
        png_get_bit_depth(png, info);

    /*
     * Normalize everything into RGBA8
     */

    if (bit_depth == 16)
    {
        png_set_strip_16(png);
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(png);
    }

    if (color_type == PNG_COLOR_TYPE_GRAY &&
        bit_depth < 8)
    {
        png_set_expand_gray_1_2_4_to_8(png);
    }

    if (png_get_valid(
            png,
            info,
            PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png);
    }

    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_filler(
            png,
            0xFF,
            PNG_FILLER_AFTER);
    }

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(png);
    }

    png_read_update_info(png, info);

    kvs_image *img =
        kvs_image_create(KVS_SIZE(width, height));

    if (!img)
    {
        png_destroy_read_struct(
            &png,
            &info,
            NULL);

        fclose(fp);

        return NULL;
    }

    png_bytep *rows =
        malloc(sizeof(png_bytep) * height);

    if (!rows)
    {
        free(kvs_image_get_pixels(img));
        free(img);

        png_destroy_read_struct(
            &png,
            &info,
            NULL);

        fclose(fp);

        return NULL;
    }

    for (int y = 0; y < height; y++)
    {
        rows[y] =
            (png_bytep)(kvs_image_get_pixels(img) +
                        y * width);
    }

    png_read_image(png, rows);

    free(rows);

    png_destroy_read_struct(
        &png,
        &info,
        NULL);

    fclose(fp);

    return img;
}