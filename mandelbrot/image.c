#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

const int HEIGHT = 2000;
const int MAX_ITER = 100;

const long double RE_START = -2;
const long double RE_END = 1;
const long double IM_START = -1;
const long double IM_END = 1;

/* ----- This code copied from https://www.lemoda.net/c/write-png/ ----- */

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}
pixel_t;

typedef struct
{
    pixel_t *pixels;
    size_t width;
    size_t height;
}
bitmap_t;

static pixel_t * pixel_at (bitmap_t * bitmap, int x, int y)
{
    return bitmap->pixels + bitmap->width * y + x;
}

static int save_png_to_file (bitmap_t *bitmap, const char *path)
{
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;
    int status = -1;
    int pixel_size = 3;
    int depth = 8;
    
    fp = fopen (path, "wb");
    if (! fp) {
        goto fopen_failed;
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }
    
    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }
    
    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }
    
    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    
    row_pointers = png_malloc (png_ptr, bitmap->height * sizeof (png_byte *));
    for (y = 0; y < bitmap->height; y++) {
        png_byte *row = 
            png_malloc (png_ptr, sizeof (uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; x++) {
            pixel_t * pixel = pixel_at (bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
        }
    }

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    status = 0;

    for (y = 0; y < bitmap->height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);

 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);
 png_create_write_struct_failed:
    fclose (fp);
 fopen_failed:
    return status;
}

/* ----- My own code from here ----- */

pixel_t colour(pixel_t* pixel, double hue) {
    double hprime = hue * 6.0;
    uint8_t x = (1.0 - fabs(fmod(hprime, 2.0)-1.0)) * 255.0;
    switch ((int)hprime) {
    case 0:
        pixel->green = x;
        pixel->red = 255;
        break;
    case 1:
        pixel->green = 255;
        pixel->red = x;
        break;
    case 2:
        pixel->blue = x;
        pixel->green = 255;
        break;
    case 3:
        pixel->blue = 255;
        pixel->green = x;
        break;
    case 4:
        pixel->blue = 255;
        pixel->red = x;
        break;
    default:
        pixel->blue = x;
        pixel->red = 255;
    }
}

int mandelbrot(long double real, long double imag) {
    long double r = 0;
    long double i = 0;
    int n = 0;
    long double rtemp;
    while (r*r + i*i <= 4 && n < MAX_ITER) {
        rtemp = r*r - i*i + real;
        i = 2*r*i + imag;
        r = rtemp;
        n++;
    }
    return n;
}

int main() {
    printf("Starting up...\n");
    long double real;
    long double imag;
    int value;
    int index;
    int WIDTH = HEIGHT * 1.5;

    bitmap_t out;
    int status;
    out.width = WIDTH;
    out.height = HEIGHT;
    out.pixels = calloc(out.width * out.height, sizeof(pixel_t));
    if (!out.pixels) {
	    return -1;
    }

    printf("Calculating...\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            real = RE_START + (x / (long double)WIDTH) * (RE_END - RE_START);
            imag = IM_START + (y / (long double)HEIGHT) * (IM_END - IM_START);
            value = mandelbrot(real, imag);
            if (value < MAX_ITER) {
                pixel_t* pixel = pixel_at(&out, x, y);
                colour(pixel, (double)value / (double)MAX_ITER);
            }
        }
    }

    printf("Saving...\n");

    if (save_png_to_file (&out, "image.png")) {
        printf("Error writing file.\n");
	    status = -1;
    }

    free(out.pixels);

    return status;
}