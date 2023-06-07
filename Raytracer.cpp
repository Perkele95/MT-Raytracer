//
// Created by arlev on 02.05.2023.
//

#include "Raytracer.h"

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
        thread = std::thread(Raytracer::compute, &shared);
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

void Raytracer::compute(SharedData *shared)
{
    while(true)
    {
        shared->mutex.lock();
        if(!shared->jobs.empty())
        {
            auto data = shared->jobs.back();
            shared->jobs.pop_back();
            shared->mutex.unlock();

            auto row = std::vector<Pixel>(data.width);
            for (int x = 0; x < data.width; ++x)
            {
                auto colour = vec3(0.0f);

                for (int32_t s = 0; s < data.samplingLevel; ++s)
                {
                    float u = (float(x) + Utils::RandFloat()) / float(data.width);
                    float v = (float(data.rowIndex) + Utils::RandFloat()) / float(data.height);
                    colour += shared->scene->getRayColour(shared->camera->getRay(u, v), 0);
                }
                colour /= float(data.samplingLevel);

                auto gammaCorrect = [](vec3<float> &v){
                    v.x = std::sqrt(v.x);
                    v.y = std::sqrt(v.y);
                    v.z = std::sqrt(v.z);
                };

                gammaCorrect(colour);

                row[x] = Vec3Cast<float, int32_t>(colour * 255.99f);
            }

            shared->mutex.lock();
            // The index math flips the image the right way
            shared->rows[data.height - data.rowIndex - 1] = std::move(row);
            shared->mutex.unlock();
        }
        else
        {
            shared->mutex.unlock();
            break;
        }
    }
}
