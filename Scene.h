//
// Created by arlev on 20.05.2023.
//

#pragma once

#include "Shared.h"

class Scene
{
public:
    explicit Scene(const RaytracingSettings *settings): st(settings){}

    void generate();
    [[nodiscard]] vec3<float> getRayColour(const Ray &ray, int32_t depth) const;

private:
    bool trace(const Ray &ray, HitData &hit) const;

    const RaytracingSettings *st;
    std::vector<std::unique_ptr<Shape>> shapes;
};
