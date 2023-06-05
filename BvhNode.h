//
// Created by arlev on 06.06.2023.
// Bounding Volume Hierarchy
//

#pragma once

#include "Shared.h"

class BvhNode : public Shape
{
public:
    BvhNode(std::unique_ptr<Shape> &&l,
            std::unique_ptr<Shape> &&r): left(std::move(l)), right(std::move(r)){}

    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &hit) const final;
    bool boundingBox(double t0, double t1, AABB &outBox) const final;

    std::unique_ptr<Shape> left;
    std::unique_ptr<Shape> right;
    AABB box;
};
