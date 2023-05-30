//
// Created by arlev on 02.05.2023.
//

#pragma once

#include "Shape.h"
#include "Utils.h"

class Material
{
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray &rayIn,
                         const HitData &hitData,
                         vec3<float> &attenuation,
                         Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(vec3<float> a): albedo(a){}

    bool scatter(const Ray &rayIn,
                 const HitData &hit,
                 vec3<float> &attenuation,
                 Ray &scattered) const override;

    vec3<float> albedo;
};

class Metal : public Material
{
public:
    Metal(vec3<float> a, float f): albedo(a), fuzz(f){}

    bool scatter(const Ray &rayIn,
                 const HitData &hit,
                 vec3<float> &attenuation,
                 Ray &scattered) const override;

    vec3<float> albedo;
    float fuzz;
};

class Dielectric : public Material
{
public:
    Dielectric(float rI): refractionIndex(rI){}

    bool scatter(const Ray &rayIn,
                 const HitData &hit,
                 vec3<float> &attenuation,
                 Ray &scattered) const override;

    float refractionIndex;
};
