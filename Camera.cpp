//
// Created by arlev on 05.05.2023.
//

#include "Camera.h"

Camera::Camera(vec3<float> lookFrom, vec3<float> lookAt, float focusDist):
    origin(lookFrom), lensRadius(RaytracerSettings::Aperture / 2.0f)
{
    const auto aspectRatio = float(RaytracerSettings::ImageX) / float(RaytracerSettings::ImageY);
    float theta = RaytracerSettings::Fov * Utils::PI32 / 180.0f;
    float halfHeight = std::tan(theta / 2.0f);
    float halfWidth = aspectRatio * halfHeight;

    front = normalise(lookFrom - lookAt);
    right = normalise(cross(WORLD_UP, front));
    up = cross(front, right);
    lowerLeft = origin - halfWidth * focusDist * right - halfHeight * focusDist * up - focusDist * front;
    horizontal = 2.0f * halfWidth * focusDist * right;
    vertical = 2.0f * halfHeight * focusDist * up;
}

Ray Camera::getRay(float s, float t) const
{
    auto rd = lensRadius * Utils::RandomInUnitDisk();
    auto offset = right * rd.x + up * rd.y;
    return {origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset};
}
