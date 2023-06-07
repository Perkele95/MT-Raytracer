//
// Created by arlev on 27.05.2023.
//

#pragma once

#include <cstddef>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>
#include <sstream>

#include "Sphere.h"
#include "Material.h"

using Pixel = vec3<int32_t>;

namespace RaytracerSettings
{
    extern std::string Filename;
    extern int32_t DepthMax;
    extern int32_t SamplingLevel;
    extern int32_t ImageX;
    extern int32_t ImageY;
    extern float Fov;
    extern float Aperture;
    extern vec3<float> Sky_bottom;
    extern vec3<float> Sky_top;
}

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
