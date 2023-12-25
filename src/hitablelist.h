//
// Created by jackson on 12/24/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_HITABLELIST_H
#define RAY_TRACER_ONE_WEEKEND_HITABLELIST_H

#include "hitable.h"

class hitable_list: public hitable {
public:
    hitable_list() = default;
    hitable_list(hitable **l, int n) { list = l; list_size = n; }
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;
    hitable **list {};
    int list_size {};
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAY_TRACER_ONE_WEEKEND_HITABLELIST_H