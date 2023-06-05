//
// Created by arlev on 05.05.2023.
//

#include "Sphere.h"

bool Sphere::hit(const Ray &ray, float tMin, float tMax, HitRecord &hit) const
{
    auto oc = ray.origin - centre;
    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if(discriminant > 0.0f)
    {
        float discriminantSqrt = std::sqrt(discriminant);
        float temp = (-b - discriminantSqrt) / a;

        if(temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.getPoint(temp);
            hit.normal = (hit.point - centre) / radius;
            hit.material = material.get();
            return true;
        }

        temp = (-b + discriminantSqrt) / a;

        if(temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.getPoint(temp);
            hit.normal = (hit.point - centre) / radius;
            hit.material = material.get();
            return true;
        }
    }
    return false;
}

bool Sphere::boundingBox(double t0, double t1, AABB &box) const
{
    box.minimum = centre - vec3(radius);
    box.maximum = centre + vec3(radius);
    return true;
}
