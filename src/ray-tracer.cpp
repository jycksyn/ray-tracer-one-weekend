#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "camera.h"
#include "sphere.h"
#include "hitablelist.h"
using namespace std;

vec3 WHITE() { return {1,1,1}; }
vec3 LIGHT_BLUE() { return {0.5,0.7,1}; }

vec3 bg_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * ( unit_direction.y() + 1 );
    return (1.0f - t) * WHITE() + t * LIGHT_BLUE();
}

vec3 random_in_unit_sphere() {
    vec3 random(
            static_cast<float>(drand48()),
            static_cast<float>(drand48()),
            static_cast<float>(drand48())
            );
    random *= 2;
    random += vec3(-1, -1, -1);
    random.make_unit_vector();
    random *= static_cast<float>(drand48());
    return random;
}

vec3 get_color(const ray &r, hitable *world) {
    hit_record rec;
    ray my_ray = r;
    float multiplier = 1;
    while (world->hit(my_ray, 0.001, MAXFLOAT, rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        multiplier *= 0.5;
        my_ray = ray(rec.p, target - rec.p);
    }
    return multiplier * bg_color(my_ray);
}

int main() {
    int nx = 200;
    int ny = 100;
    int rays_per_pixel = 100;

    camera cam;

    hitable * list[2];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0);
    hitable *world = new hitable_list(list, 2);

    vector<char> pixels;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            vec3 color = {0,0,0};
            for (int s = 0; s < rays_per_pixel; s++) {
                float u = float(drand48() + x) / float(nx);
                float v = float(drand48() + y) / float(ny);
                ray r = cam.get_ray(u, v);
                color += get_color(r, world);
            }
            color /= float(rays_per_pixel);
            pixels.push_back(char(255.99 * color.r()));
            pixels.push_back(char(255.99 * color.g()));
            pixels.push_back(char(255.99 * color.b()));
        }
    }

    stbi_write_png("u.png", nx, ny, 3, &pixels[0], 3 * nx);
}