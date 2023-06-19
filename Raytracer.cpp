//
// Created by arlev on 02.05.2023.
//

#include "Raytracer.h"
#include "Compute.h"

namespace RaytracerSettings
{
    std::string Filename = "raytraced";
    int32_t DepthMax = 50;
    int32_t SamplingLevel = 100;
    int32_t ImageX = 300;
    int32_t ImageY = 200;
    float Fov = 23.0f;
    float Aperture = 0.2f;
    vec3<float> Sky_bottom = vec3(1.0f);
    vec3<float> Sky_top = Utils::Colour(45, 151, 237);
}

Raytracer::Raytracer(): scene()
{
    scene.generate();
    createImage();
}

void Raytracer::createImage()
{
    std::ofstream output(RaytracerSettings::Filename + ".ppm");
    output << "P3\n" << RaytracerSettings::ImageX << " " << RaytracerSettings::ImageY << "\n255\n";

    const auto lookFrom = vec3(12.0f, 1.6f, 2.5f);
    const auto lookAt =  vec3(0.0f, 0.0f, 0.0f);

    float focalLength = length(lookFrom - lookAt);
    auto camera = Camera(lookFrom, lookAt, focalLength);

    SharedData shared{};
    shared.scene = &scene;
    shared.camera = &camera;
    shared.jobs.resize(RaytracerSettings::ImageY);
    shared.rows.resize(RaytracerSettings::ImageY);

    for (int32_t i = 0; i < RaytracerSettings::ImageY; i++)
    {
        shared.jobs[i].width = RaytracerSettings::ImageX;
        shared.jobs[i].height = RaytracerSettings::ImageY;
        shared.jobs[i].rowIndex = i;
        shared.jobs[i].samplingLevel = RaytracerSettings::SamplingLevel;
    }

    auto threadCount = std::thread::hardware_concurrency();

    if(threadCount == 0)
        threadCount = 1;

    std::vector<std::thread> threads(threadCount);

    for (auto &thread : threads)
    {
        thread = std::thread(Compute, &shared);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    for (const auto &row : shared.rows)
    {
        for (const auto &pixel : row)
        {
            output << pixel.x << " " << pixel.y << " " << pixel.z << "\n";
        }
    }
}
