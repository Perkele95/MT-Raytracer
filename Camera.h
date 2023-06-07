//
// Created by arlev on 05.05.2023.
//

#pragma once

#include "Shared.h"

const auto PI32 = 3.14159265359f; // TODO: move to Utils

class Camera
{
    constexpr static auto WORLD_UP = vec3<float>(0.0f, 1.0f, 0.0f);

public:
    Camera(vec3<float> lookFrom, vec3<float> lookAt, float focusDist);

    [[nodiscard]] Ray getRay(float s, float t) const;

    vec3<float> origin, lowerLeft, horizontal, vertical;
    vec3<float> up, right, front;
    float lensRadius;
};
