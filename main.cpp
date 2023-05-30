#include <iostream>

#include "Raytracer.h"

int main()
{
    try
    {
        RaytracingSettings settings;
        settings.imageX = 1280;
        settings.imageY = 720;
        settings.samplingLevel = 150;
        settings.aperture = 0.27f;
        settings.filename = "raytraced";
        auto rt = Raytracer(settings);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}
