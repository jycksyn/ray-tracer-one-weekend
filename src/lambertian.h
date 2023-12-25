//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_LAMBERTIAN_H
#define RAY_TRACER_ONE_WEEKEND_LAMBERTIAN_H


#include "material.h"

class lambertian : public material {

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;

    vec3 albedo;
public:
    explicit lambertian(const vec3 &a) { albedo = a; }
};

bool lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target - rec.p);
    attenuation = this->albedo;
    return true;
}


#endif //RAY_TRACER_ONE_WEEKEND_LAMBERTIAN_H
