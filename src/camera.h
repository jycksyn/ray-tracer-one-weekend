//
// Created by jackson on 12/25/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_CAMERA_H
#define RAY_TRACER_ONE_WEEKEND_CAMERA_H

#include"ray.h"

class camera {
public:
    camera(
            vec3 lookfrom,
            vec3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio,
            double focus_dist
    ) {
    vec3 u, v, w;
    auto theta = vfov * M_PIf / 180.f;
    auto h = tan(theta/2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    o = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left = o - horizontal/2 - vertical/2 - focus_dist*w;
}

    ray get_ray(float u, float v) const {
        return {o, lower_left + u*horizontal + v*vertical - o};
    }

    vec3 lower_left;
    vec3 horizontal;
    vec3 vertical;
    vec3 o;
};

#endif //RAY_TRACER_ONE_WEEKEND_CAMERA_H
