//
// Created by arlev on 02.05.2023.
//

#pragma once

#include "vec.h"

class Ray
{
public:
    Ray() = default;
    Ray(const vec3<float> &o, const vec3<float> &d): origin(o), direction(d){}

    vec3<float> getPoint(float t)
    {
        return origin + direction * t;
    }

    vec3<float> getPoint(float t) const
    {
        return origin + direction * t;
    }

    vec3<float> origin, direction;
};