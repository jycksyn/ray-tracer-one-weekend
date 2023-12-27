//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_METAL_H
#define RAY_TRACER_ONE_WEEKEND_METAL_H


#include "material.h"

class metal : public material {
public:

    explicit metal(const vec3 &a, const float &f) {
        albedo = a;
        if (f > 1) fuzz = 1;
        else fuzz = f;
    }

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;

    vec3 albedo;
    float fuzz;
};

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 target = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, target + fuzz * random_in_unit_sphere());
    attenuation = this->albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}


#endif //RAY_TRACER_ONE_WEEKEND_METAL_H
