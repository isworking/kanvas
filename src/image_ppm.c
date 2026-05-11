#include <kvs/image.h>

#include <stdio.h>
#include <string.h>

bool kvs_image_write_ppm(
    const kvs_image *img,
    const char *path)
{
    FILE *fp = fopen(path, "wb");

    if (!fp)
    {
        return false;
    }

    int img_width = kvs_image_get_width(img);
    int img_height = kvs_image_get_height(img);

    fprintf(
        fp,
        "P6\n%d %d\n255\n",
        img_width,
        img_height);

    for (int y = 0; y < img_height; y++)
    {
        for (int x = 0; x < img_width; x++)
        {
            kvs_color color =
                kvs_image_get_pixels(img)[y * img_width + x];

            fputc(color.r, fp);
            fputc(color.g, fp);
            fputc(color.b, fp);
        }
    }

    fclose(fp);

    return true;
}

kvs_image *kvs_image_read_ppm(const char *path)
{
    FILE *fp = fopen(path, "rb");

    if (!fp)
        return NULL;

    char magic[3] = {0};

    if (fscanf(fp, "%2s", magic) != 1)
    {
        fclose(fp);
        return NULL;
    }

    if (strcmp(magic, "P6") != 0)
    {
        fclose(fp);
        return NULL;
    }

    int width = 0;
    int height = 0;
    int maxval = 0;

    if (fscanf(fp, "%d %d", &width, &height) != 2)
    {
        fclose(fp);
        return NULL;
    }

    if (fscanf(fp, "%d", &maxval) != 1)
    {
        fclose(fp);
        return NULL;
    }

    if (maxval != 255)
    {
        fclose(fp);
        return NULL;
    }

    fgetc(fp);

    kvs_image *img = kvs_image_create(KVS_SIZE(width, height));

    if (!img)
    {
        fclose(fp);
        return NULL;
    }

    size_t pixel_count = (size_t)width * (size_t)height;

    for (size_t i = 0; i < pixel_count; i++)
    {
        kvs_color *color = &kvs_image_get_pixels(img)[i];

        int r = fgetc(fp);
        int g = fgetc(fp);
        int b = fgetc(fp);

        if (r == EOF || g == EOF || b == EOF)
        {
            kvs_image_destroy(img);
            fclose(fp);
            return NULL;
        }

        color->r = (kvs_u8)r;
        color->g = (kvs_u8)g;
        color->b = (kvs_u8)b;
    }

    fclose(fp);

    return img;
}