#include <memory>
#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "camera.h"
#include "sphere.h"
#include "hitablelist.h"
#include "lambertian.h"
#include "metal.h"
#include "vec3.h"

using namespace std;

vec3 WHITE() { return {1,1,1}; }
vec3 LIGHT_BLUE() { return {0.5,0.7,1}; }

vec3 bg_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * ( unit_direction.y() + 1 );
    return (1.0f - t) * WHITE() + t * LIGHT_BLUE();
}

vec3 get_color(const ray &r, hitable *world) {
    hit_record rec;
    ray my_ray = r;
    vec3 attenuation(1,1,1);
    for (int depth = 0; world->hit(my_ray, 0.001, MAXFLOAT, rec) && depth < 50; depth++) {
        vec3 a;
        if (rec.mat_ptr->scatter(my_ray, rec, a, my_ray)) {
            attenuation *= a;
        }
    }
    return attenuation * bg_color(my_ray);
}

int main() {
    int nx = 200;
    int ny = 100;
    int rays_per_pixel = 100;

    camera cam;

    hitable * list [3];
    list[0] = new sphere(vec3(0.5, 0.0, -1.0), 0.5f, std::make_shared<lambertian>(vec3(0.5, 0.5, 0.5)));
    list[1] = new sphere(vec3(-0.5, 0.0, -1.0), 0.5f, std::make_shared<metal>(vec3(0.75, 0, 0.75)));
    list[2] = new sphere(vec3(0.0, -100.5, -1.0), 100.0, std::make_shared<lambertian>(vec3(0.5, 0, 0)));
    hitable *world = new hitable_list(list, 3);

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