//
// Created by jackson on 12/24/23.
//

#ifndef RAY_TRACER_ONE_WEEKEND_HITABLELIST_H
#define RAY_TRACER_ONE_WEEKEND_HITABLELIST_H

#include "hitable.h"
#include <iterator>

template<class HitableIterator>
class hitable_list: public hitable {
public:
    hitable_list() = default;
    hitable_list(
            const HitableIterator &first,
            const HitableIterator &last) {
        this->first = first;
        this->last = last;
    }
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const override;

    HitableIterator first;
    HitableIterator last;
};

template<class HitableIterator>
bool hitable_list<HitableIterator>::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for (auto cur = first; cur != last; cur++) {
        hitable & x = *(*cur);
        if (x.hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAY_TRACER_ONE_WEEKEND_HITABLELIST_H
