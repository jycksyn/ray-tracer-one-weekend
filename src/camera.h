//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_CAMERA_H
#define RAY_TRACER_ONE_WEEKEND_CAMERA_H

#include"ray.h"

class camera {
public:
    camera() {
        lower_left = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        o = vec3(0.0, 0.0, 0.0);
    };

    ray get_ray(float u, float v) const {
        return {o, lower_left + u*horizontal + v*vertical};
    }

    vec3 lower_left;
    vec3 horizontal;
    vec3 vertical;
    vec3 o;
};

#endif //RAY_TRACER_ONE_WEEKEND_CAMERA_H
