//
// Created by arlev on 01.06.2023.
//

#include "AABB.h"

bool AABB::hit(const Ray &ray, double t_min, double t_max) const
{
    for (int32_t i = 0; i < 3; ++i)
    {
        const auto invDir = 1.0f / ray.direction[i];
        auto t0 = (minimum[i] - ray.origin[i]) * invDir;
        auto t1 = (maximum[i] - ray.origin[i]) * invDir;

        if(invDir < 0.0f)
            std::swap(t0, t1);

        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;

        if(t_max <= t_min)
            return false;
    }
    return true;
}
