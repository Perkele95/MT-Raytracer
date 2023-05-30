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

#include "Camera.h"
#include "Sphere.h"
#include "Material.h"

using Pixel = vec3<int32_t>;

struct RaytracingSettings
{
    std::string filename;
    int32_t depthMax = 50;
    int32_t samplingLevel = 100;
    int32_t imageX = 300;
    int32_t imageY = 200;
    float fov = 23.0f;
    float aperture = 0.2f;
    vec3<float> sky_bottom = vec3(1.0f);
    vec3<float> sky_top = Utils::Colour(45, 151, 237);
};

struct ComputeJob
{
    int32_t rowIndex;
    int32_t width;
    int32_t height;
    int32_t samplingLevel;
};

struct Scene;

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
