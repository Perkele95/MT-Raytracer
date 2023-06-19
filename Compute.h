//
// Created by arlev on 07.06.2023.
//

#pragma once

#include "Shared.h"

struct ComputeJob
{
    int32_t rowIndex;
    int32_t width;
    int32_t height;
    int32_t samplingLevel;
};

struct Scene;
struct Camera;

struct SharedData
{
    // Read only

    const Scene *scene;
    const Camera *camera;

    // Mutex locked shared resources

    std::vector<ComputeJob> jobs;
    std::vector<std::vector<Pixel> > rows;

    std::mutex mutex;
};

void Compute(SharedData *shared)
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
