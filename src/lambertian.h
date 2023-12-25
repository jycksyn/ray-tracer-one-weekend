//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_LAMBERTIAN_H
#define RAY_TRACER_ONE_WEEKEND_LAMBERTIAN_H


#include "material.h"

class lambertian : public material {
    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;
    [[nodiscard]] virtual vec3 albedo(const hit_record &rec) const = 0;
};

bool lambertian::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target - rec.p);
    attenuation = this->albedo(rec);
    return true;
}

class matte_color : public lambertian {
public:
    explicit matte_color(const vec3 &a) { color = a; }
    [[nodiscard]] vec3 albedo(const hit_record &rec) const override {
        return color;
    }

    vec3 color;
};


#endif //RAY_TRACER_ONE_WEEKEND_LAMBERTIAN_H
