//
// Created by arlev on 03.05.2023.
//

#include <random>

#include "Utils.h"

namespace Utils
{
    static std::random_device device;
    static std::mt19937 generator(device());
    static std::uniform_real_distribution<> realDistribution(0.0f, 0.9999999f);

    float RandFloat()
    {
        return static_cast<float>(realDistribution(generator));
    }

    int32_t RandInt(int32_t min, int32_t max)
    {
        std::uniform_int_distribution<> intDistribution(min, max);
        return intDistribution(generator);
    }

    vec3<float> RandomInUnitSphere()
    {
        auto v = 2.0f * vec3(RandFloat(), RandFloat(), RandFloat()) - vec3(1.0f);
        return normalise(v) * RandFloat();
    }

    vec3<float> RandomInUnitDisk()
    {
        auto v = 2.0f * vec3(RandFloat(), RandFloat(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
        return normalise(v) * RandFloat();
    }

    vec3<float> Reflect(vec3<float> a, vec3<float> b)
    {
        return a - 2.0f * dot(a, b) * b;
    }

    bool Refract(vec3<float> a, vec3<float> b, float niOverNt, vec3<float> &refracted)
    {
        auto uv = normalise(a);
        float dt = dot(uv, b);
        float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);
        if(discriminant > 0.0f)
        {
            refracted = niOverNt * (uv - b * dt) - b * std::sqrt(discriminant);
            return true;
        }
        return false;
    }

    float Schlick(float cosine, float refractionIndex)
    {
        float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
        r0 *= r0;
        return r0 + (1.0f - r0) * float(std::pow(1.0f - cosine, 5));
    }
}