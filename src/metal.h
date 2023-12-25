//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_METAL_H
#define RAY_TRACER_ONE_WEEKEND_METAL_H


#include "material.h"

class metal : public material {
public:

    explicit metal(const vec3 &a) { albedo = a; }

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;

    vec3 albedo;
};

bool metal::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 target = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, target);
    attenuation = this->albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}


#endif //RAY_TRACER_ONE_WEEKEND_METAL_H
