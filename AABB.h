//
// Created by arlev on 01.06.2023.
//

#pragma once

#include "Ray.h"

class AABB
{
public:
    AABB() = default;
    AABB(const vec3<float> min, const vec3<float> max): minimum(min), maximum(max){}

    [[nodiscard]] bool hit(const Ray& ray, double t_min, double t_max) const;

    static AABB Combine(const AABB &a, const AABB &b);

    vec3<float> minimum{}, maximum{};
};
