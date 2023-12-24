#include<iostream>
#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

int main() {
    int nx = 200;
    int ny = 100;
    char * pixels = new char[nx * ny * 3];
    int i = 0;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            float r = float(x) / float(nx);
            float g = float(y) / float(ny);
            float b = 0.2;
            pixels[i++] = char(255.99 * r);
            pixels[i++] = char(255.99 * g);
            pixels[i++] = char(255.99 * b);
        }
    }
    stbi_write_png("foo.png", nx, ny, 3, pixels, 3 * nx);
}