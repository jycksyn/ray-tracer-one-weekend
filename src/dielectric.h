//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_DIELECTRIC_H
#define RAY_TRACER_ONE_WEEKEND_DIELECTRIC_H


#include "material.h"

float schlick(float cosine, float ref_idx) {
    float r0 = (1-ref_idx) / (1 + ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*powf(1-cosine, 5);
}

class dielectric : public material {
public:

    dielectric(const float &ref_index) : albedo(1, 1, 1) {
        this->ref_index = ref_index;
    };

    explicit dielectric(const vec3 &a, const float &ref_index) {
        albedo = a;
        this->ref_index = ref_index;
    }

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override;

    vec3 albedo;
    float ref_index;
};

bool dielectric::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ratio;
    attenuation = albedo;
    vec3 refracted;
    float cosine = dot(unit_vector(r_in.direction()), rec.normal);
    if (cosine > 0) {
        outward_normal = -rec.normal;
        ratio = ref_index;
        cosine *= ref_index;
    } else {
        outward_normal = rec.normal;
        ratio = 1 / ref_index;
        cosine *= -1;
    }
    bool light_refracts = refract(r_in.direction(), outward_normal, ratio, refracted);
    float reflect_prob = 1;
    if (light_refracts) {
        reflect_prob = schlick(cosine, ref_index);
    }

    if (drand48() < reflect_prob) {
        scattered = ray(rec.p, reflected);
    } else {
        scattered = ray(rec.p, refracted);
    }
    return true;
}


#endif //RAY_TRACER_ONE_WEEKEND_DIELECTRIC_H
