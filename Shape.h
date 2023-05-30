//
// Created by arlev on 02.05.2023.
//

#pragma once

#include "Ray.h"

struct Material;

struct HitData
{
    float t;
    vec3<float> point;
    vec3<float> normal;
    Material *material;
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitData &hit) const = 0;
};