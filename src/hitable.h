//
// Created by jackson on 12/24/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_HITABLE_H
#define RAY_TRACER_ONE_WEEKEND_HITABLE_H

#include <memory>
#include "ray.h"

class material;

struct hit_record {
    float t {};
    vec3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif //RAY_TRACER_ONE_WEEKEND_HITABLE_H
