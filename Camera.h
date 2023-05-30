//
// Created by arlev on 05.05.2023.
//

#pragma once

#include "Ray.h"

const auto WORLD_UP = vec3<float>(0.0f, 1.0f, 0.0f);
const auto PI32 = 3.14159265359f;

class Camera
{
public:
    Camera(vec3<float> lookFrom, vec3<float> lookAt, float fov, float aspectRatio, float aperture, float focusDist);

    Ray getRay(float s, float t) const;

    vec3<float> origin, lowerLeft, horizontal, vertical;
    vec3<float> up, right, front;
    float lensRadius;
};
