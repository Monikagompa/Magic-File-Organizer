#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#define WIDTH 1000
#define HEIGHT 1000
#define COLOR_DEPTH 8

struct Pixel {
    png_byte r, g, b, a;
};

int main(int argc, char *argv[]) {

    // Input check
    if (argc < 2) {
        printf("Usage: ./app.exe WORD contains only letters H,E,L,O\n");
        return 1;
    }
    char *word = argv[1];

    FILE *f = fopen("out.png", "wb");
    if (!f) {
        fprintf(stderr, "could not open out.png\n");
        return 1;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) return 1;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(f);
        return 1;
    }

    png_init_io(png_ptr, f);

    png_set_IHDR(png_ptr, info_ptr, WIDTH, HEIGHT, COLOR_DEPTH,
                 PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    // Allocate rows
    struct Pixel *row_pointers[HEIGHT];

    // Fill white background
    for (int y = 0; y < HEIGHT; y++) {
        row_pointers[y] = (struct Pixel *)calloc(WIDTH, sizeof(struct Pixel));

        for (int x = 0; x < WIDTH; x++) {
            row_pointers[y][x].r = 255;
            row_pointers[y][x].g = 255;
            row_pointers[y][x].b = 255;
            row_pointers[y][x].a = 255;
        }
    }

    int blockSize = 20;
    int startX = 50;
    int startY = 100;
    int spacing = 10;

    // Patterns
    int H[5][5] = {
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1}
    };

    int E[5][5] = {
        {1,1,1,1,1},
        {1,0,0,0,0},
        {1,1,1,1,0},
        {1,0,0,0,0},
        {1,1,1,1,1}
    };

    int L[5][5] = {
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,0,0,0,0},
        {1,1,1,1,1}
    };

    int O[5][5] = {
        {0,1,1,1,0},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {0,1,1,1,0}
    };

    // Loop through input word
    for (int i = 0; word[i] != '\0'; i++) {

        char ch = word[i];
        int (*pattern)[5] = NULL;

        if (ch == 'H') pattern = H;
        else if (ch == 'E') pattern = E;
        else if (ch == 'L') pattern = L;
        else if (ch == 'O') pattern = O;
        else continue; // skip unsupported

        int currentX = startX + i * (5 * blockSize + spacing);

        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {

                if (pattern[row][col] == 1) {

                    int screenX = currentX + col * blockSize;
                    int screenY = startY + row * blockSize;

                    for (int y = screenY; y < screenY + blockSize && y < HEIGHT; y++) {
                        for (int x = screenX; x < screenX + blockSize && x < WIDTH; x++) {
                            row_pointers[y][x].r = 0;
                            row_pointers[y][x].g = 244;
                            row_pointers[y][x].b = 0;
                            row_pointers[y][x].a = 255;
                        }
                    }
                }
            }
        }
    }

    png_write_image(png_ptr, (png_byte **)row_pointers);
    png_write_end(png_ptr, NULL);

    // Free memory
    for (int y = 0; y < HEIGHT; y++) {
        free(row_pointers[y]);
    }

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(f);

    return 0;
}