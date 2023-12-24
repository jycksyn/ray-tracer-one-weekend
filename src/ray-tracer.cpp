#include<iostream>
#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
using namespace std;

int main() {
    int nx = 200;
    int ny = 100;
    char * pixels = new char[nx * ny * 3];
    int i = 0;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            vec3 color(float(x) / float(nx), float(y) / float(ny), 1);
            pixels[i++] = char(255.99 * color.r());
            pixels[i++] = char(255.99 * color.g());
            pixels[i++] = char(255.99 * color.b());
        }
    }
    stbi_write_png("foo.png", nx, ny, 3, pixels, 3 * nx);
}