#include<memory>
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
#include "dielectric.h"
#include "vec3.h"
#include "textured.h"

using namespace std;

vec3 WHITE() { return {1,1,1}; }
vec3 LIGHT_BLUE() { return {0.5,0.7,1}; }

vec3 bg_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * ( unit_direction.y() + 1 );
    return (1.0f - t) * WHITE() + t * LIGHT_BLUE();
}

vec3 get_color(const ray &r, const hitable & world) {
    hit_record rec;
    ray my_ray = r;
    vec3 attenuation(1,1,1);
    for (int depth = 0; world.hit(my_ray, 0.001, MAXFLOAT, rec) && depth < 50; depth++) {
        vec3 a;
        if (rec.mat_ptr->scatter(my_ray, rec, a, my_ray)) {
            attenuation *= a;
        }
    }
    return attenuation * bg_color(my_ray);
}

int main() {
    int nx = 500;
    int ny = 250;
    int rays_per_pixel = 100;

    camera cam({0,0,0}, {0, 0, -1}, {0, 1, 0}, 90, float(nx) / float(ny), 1);

    vector<shared_ptr<hitable>> obj_list;
    vec3 c1(0.5, 0.0, -1.0);

    int width, height, channels;
    uint8_t * pp = stbi_load("./map.JPG", &width, &height, &channels, 3);

    if (pp == nullptr) {
      cout << "Image not found" << endl;
    }

    obj_list.push_back(make_shared<sphere>(c1, 0.5f, std::make_shared<matte_textured>(c1, width, height, channels, &pp)));
//    obj_list.push_back(make_shared<sphere>(vec3(-0.5, 0.0, -1.0), 0.5f, std::make_shared<dielectric>( 1.5)));
//    obj_list.push_back(make_shared<sphere>(vec3(-0.5, 0.0, -1.0), 0.5f, std::make_shared<dielectric>( 1.5)));
    obj_list.push_back(make_shared<sphere>(vec3(-0.5, 0.0, -1.0), 0.5f, std::make_shared<metal>(vec3(0.8,0.6,0.2), 0)));
    obj_list.push_back(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, std::make_shared<matte_color>(vec3(0.5, 0, 0))));
    hitable_list<typeof obj_list.begin()> world(obj_list.begin(), obj_list.end());

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

    stbi_write_png("test.png", nx, ny, 3, &pixels[0], 3 * nx);
}