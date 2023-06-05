//
// Created by arlev on 05.05.2023.
//

#pragma once

#include <memory>

#include "Shape.h"
#include "Material.h"

class Sphere : public Shape
{
public:
    Sphere() = default;
    Sphere(vec3<float> c, float r, std::unique_ptr<Material> &&m): centre(c), radius(r), material(std::move(m)){}

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &hit) const final;
    bool boundingBox(double t0, double t1, AABB &box) const final;

    vec3<float> centre{};
    float radius{};
    std::unique_ptr<Material> material;
};
