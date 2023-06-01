//
// Created by arlev on 02.05.2023.
//

#pragma once

#include "Scene.h"

class Raytracer
{
public:
    explicit Raytracer(const RaytracingSettings &settings);

private:
    void createImage();

    static void compute(SharedData *shared);

    RaytracingSettings  st;
    Scene               scene;
};
