//
// Created by arlev on 20.05.2023.
//

#pragma once

#include "Shared.h"

class Scene
{
    constexpr static auto T_MIN = 0.001f;
    constexpr static auto T_MAX = float(0xffffffff);

public:
    Scene() = default;

    void generate();
    [[nodiscard]] vec3<float> getRayColour(const Ray &ray, int32_t depth) const;

private:
    bool trace(const Ray &ray, HitRecord &hit) const;
    bool getBounds(double t0, double t1, AABB &box) const;

    std::vector<std::unique_ptr<Shape>> shapes;
};
