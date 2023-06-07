#include <iostream>

#include "Raytracer.h"

int main()
{
    try
    {
        RaytracerSettings::ImageX = 1280;
        RaytracerSettings::ImageY = 720;
        RaytracerSettings::SamplingLevel = 2;
        RaytracerSettings::Aperture = 0.27f;
        RaytracerSettings::Filename = "raytraced";
        auto rt = Raytracer();
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}
