//
// Created by jackson on 12/24/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_SPHERE_H
#define RAY_TRACER_ONE_WEEKEND_SPHERE_H

#include <utility>

#include "vec3.h"
#include "material.h"

class sphere: public hitable {
public:
    sphere() = default;
    sphere(vec3 cen, float r, std::shared_ptr<material> mat) : center(cen), radius(r), mat_ptr(std::move(mat)) {}
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
    vec3 center;
    float radius{};
    std::shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    vec3 oc = r.origin() - center;
    float a = r.direction().squared_length();
    float b = dot(oc, r.direction());
    float c = oc.squared_length() - radius*radius;

    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float parameter = (-b - sqrt(discriminant)) / a;
        if (parameter < t_max && parameter > t_min) {
            rec.t = parameter;
            rec.p = r.point_at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        parameter = (-b + sqrt(discriminant)) / a;
        if (parameter < t_max && parameter > t_min) {
            rec.t = parameter;
            rec.p = r.point_at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif //RAY_TRACER_ONE_WEEKEND_SPHERE_H
