//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_MATERIAL_H
#define RAY_TRACER_ONE_WEEKEND_MATERIAL_H

#include "hitable.h"

class material {
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
    virtual ~material() = default;
};

#endif //RAY_TRACER_ONE_WEEKEND_MATERIAL_H
