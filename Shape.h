//
// Created by arlev on 02.05.2023.
//

#pragma once

#include "Ray.h"

struct Material;

struct HitRecord
{
    float t = 0.0f;
    vec3<float> point = {};
    vec3<float> normal = {};
    Material *material = nullptr;
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &hit) const = 0;
};