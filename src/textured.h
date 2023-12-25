//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_TEXTURED_H
#define RAY_TRACER_ONE_WEEKEND_TEXTURED_H

#include"lambertian.h"
#include "sphere.h"

class matte_textured : public lambertian {
public:
    explicit matte_textured(const vec3 &center, const int &width, const int &height, const int &channels, uint8_t ** pixels) {
        this->width = width;
        this->height = height;
        this->channels = channels;
        this->center = center;
        this->pixels = *pixels;
    }
    [[nodiscard]] vec3 albedo(const hit_record &rec) const override {
        vec3 oc = rec.p - center;
        oc.make_unit_vector();
        float horizontal = atanf(-oc.z() / oc.x());
        if (horizontal < 0)
            horizontal += 3.14;
        if (horizontal < 0)
            horizontal += 3.14;
        horizontal /= 6.2;

        // Cylindrical Projection
        float vertical = (-oc.y() + 1.0f) / 2.0f;

        // Spherical Coordinates or Mercator Projection
//      float vertical = acosf(oc.y()) / M_PIf;

        int size = width * channels * height;

        int x = int(horizontal * width);
        int y = int(vertical * height);

        int pixel = int(width * channels * y) + int(channels * x);

        vec3 output(
                static_cast<float>(pixels[pixel + 0]) / 255.99f,
                static_cast<float>(pixels[pixel + 1]) / 255.99f,
                static_cast<float>(pixels[pixel + 2]) / 255.99f
                );

        return output;
    }

    int width{};
    int height{};
    int channels{};
    uint8_t * pixels;
    vec3 center;
};

#endif //RAY_TRACER_ONE_WEEKEND_TEXTURED_H
