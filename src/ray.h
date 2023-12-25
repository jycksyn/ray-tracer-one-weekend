//
// Created by jackson on 12/24/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_RAY_H
#define RAY_TRACER_ONE_WEEKEND_RAY_H
#include "vec3.h"

class ray
{
public:
    ray()= default;
    ray(const vec3&origin, const vec3&direction) {
        this->A = origin;
        this->B = direction;
    }
    [[nodiscard]] vec3 origin() const { return A; }
    [[nodiscard]] vec3 direction() const { return B; }
    [[nodiscard]] vec3 point_at(float t) const { return A + t*B; }

    vec3 A;
    vec3 B;
};

#endif //RAY_TRACER_ONE_WEEKEND_RAY_H