#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "ray.h"
using namespace std;

vec3 WHITE() { return {1,1,1}; }
vec3 LIGHT_BLUE() { return {0.5,0.7,1}; }

vec3 bg_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * ( unit_direction.y() + 1 );
    return (1.0f - t) * WHITE() + t * LIGHT_BLUE();
}

int main() {
    int nx = 200;
    int ny = 100;

    vec3 lower_left(-2, -1, -1);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 o(0, 0, 0);

    auto * pixels = new u_int8_t[nx * ny * 3];
    int i = 0;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            float u = float(x) / float(nx);
            float v = float(y) / float(ny);
            ray r(o, lower_left + u*horizontal + v*vertical);
            vec3 color = bg_color(r);
            pixels[i++] = u_int8_t(255.99 * color.r());
            pixels[i++] = u_int8_t(255.99 * color.g());
            pixels[i++] = u_int8_t(255.99 * color.b());
        }
    }
    stbi_write_png("foo.png", nx, ny, 3, pixels, 3 * nx);
}