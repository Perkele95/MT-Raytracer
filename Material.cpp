//
// Created by arlev on 03.05.2023.
//

#include "Material.h"

bool Lambertian::scatter(const Ray &rayIn, const HitData &hit, vec3<float> &attenuation, Ray &scattered) const
{
    scattered = Ray(hit.point, hit.normal + Utils::RandomInUnitSphere());
    attenuation = albedo;
    return true;
}

bool Metal::scatter(const Ray &rayIn, const HitData &hit, vec3<float> &attenuation, Ray &scattered) const
{
    auto reflected = Utils::Reflect(rayIn.direction, hit.normal);
    scattered = Ray(hit.point, reflected + fuzz * Utils::RandomInUnitSphere());
    attenuation = albedo;

    // Return true if the newly scattered ray is going away from the surface
    return dot(scattered.direction, hit.normal) > 0.0f;
}

bool Dielectric::scatter(const Ray &rayIn, const HitData &hit, vec3<float> &attenuation, Ray &scattered) const
{
    auto reflected = Utils::Reflect(rayIn.direction, hit.normal);
    attenuation = vec3(1.0f);

    vec3<float> outwardNormal, refracted;
    float niOverNt = 0.0f, reflectProb = 1.0f, cosine = 0.0f;

    if(dot(rayIn.direction, hit.normal) > 0.0f)
    {
        outwardNormal = -hit.normal;
        niOverNt = refractionIndex;
        cosine = refractionIndex * dot(rayIn.direction, hit.normal) / length(rayIn.direction);
    }
    else
    {
        outwardNormal = hit.normal;
        niOverNt = 1.0f / refractionIndex;
        cosine = -dot(rayIn.direction, hit.normal) / length(rayIn.direction);
    }

    if(Utils::Refract(rayIn.direction, outwardNormal, niOverNt, refracted))
        reflectProb = Utils::Schlick(cosine, refractionIndex);

    scattered = Utils::RandFloat() < reflectProb ? Ray(hit.point, reflected) : Ray(hit.point, refracted);
    return true;
}
