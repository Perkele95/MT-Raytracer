//
// Created by arlev on 02.05.2023.
//

#pragma once

#include "Scene.h"
#include "Camera.h"

class Raytracer
{
public:
    Raytracer();

private:
    void createImage();

    Scene                       scene;
};
