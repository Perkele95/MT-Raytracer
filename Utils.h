//
// Created by arlev on 03.05.2023.
//

#pragma once

#include "Ray.h"

namespace Utils
{
    constexpr float PI32 = 3.141592741f;
    constexpr double PI64 = 3.141592653589793;

    float RandFloat();
    int32_t RandInt(int32_t min, int32_t max);
    vec3<float> RandomInUnitSphere();
    vec3<float> RandomInUnitDisk();
    vec3<float> Reflect(vec3<float> a, vec3<float> b);
    bool Refract(vec3<float> a, vec3<float> b, float niOverNt, vec3<float> &out);
    float Schlick(float cosine, float refractionIndex);

    constexpr vec3<float> Colour(uint8_t r, uint8_t g, uint8_t b)
    {
        auto c = vec3<float>(Vec3Cast<uint8_t, float>(vec3(r, g, b)));
        return c / 255.0f;
    }
}