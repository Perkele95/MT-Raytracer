//
// Created by arlev on 20.05.2023.
//

#include "Scene.h"

void Scene::generate()
{
    constexpr auto COLOUR_ORANGE = Utils::Colour(255, 170, 66);
    constexpr auto COLOUR_BLUE = Utils::Colour(38, 85, 166);
    constexpr auto COLOUR_GROUND = Utils::Colour(68, 78, 79);

    constexpr int32_t X_RANGE = 11;
    constexpr int32_t Y_RANGE = 11;

    shapes.reserve(4 * (X_RANGE * Y_RANGE + 1));

    // Ground
    shapes.emplace_back(std::make_unique<Sphere>(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_unique<Lambertian>(COLOUR_GROUND)));

    // Three big spheres
    shapes.emplace_back(std::make_unique<Sphere>(vec3(4.0f, 0.7f, 0.0f), 0.7f, std::make_unique<Lambertian>(vec3(1.0f, 1.0f, 1.0f))));
    shapes.emplace_back(std::make_unique<Sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Metal>(vec3(0.17f, 0.28f, 0.46f), 0.2f)));
    shapes.emplace_back(std::make_unique<Sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, std::make_unique<Dielectric>(1.5f)));

    for (int x = -X_RANGE; x < X_RANGE; ++x)
    {
        for (int y = -Y_RANGE; y < Y_RANGE; ++y)
        {
            const auto radius = Utils::RandFloat() * 0.15f + 0.1f;
            const auto centre = vec3(float(x) + 0.9f * Utils::RandFloat(), radius, y * 0.9f * Utils::RandFloat());

            if(length(centre - vec3(4.0f, 0.2f, 0.0f)) > 0.9f)
            {
                const float randValue = Utils::RandFloat();

                if(randValue < 0.7f)
                {
                    const auto albedo = Utils::RandFloat() * COLOUR_BLUE;
                    shapes.emplace_back(std::make_unique<Sphere>(centre, radius, std::make_unique<Lambertian>(albedo)));
                }
                else if(randValue < 0.95f)
                {
                    const auto albedo = Utils::RandFloat() * COLOUR_ORANGE;
                    shapes.emplace_back(std::make_unique<Sphere>(centre, radius, std::make_unique<Metal>(albedo, 0.5f * Utils::RandFloat())));
                }
                else
                {
                    shapes.emplace_back(std::make_unique<Sphere>(centre, radius, std::make_unique<Dielectric>(1.5f)));
                }
            }
        }
    }
}

vec3<float> Scene::getRayColour(const Ray &ray, int32_t depth) const
{
    HitData hit{};

    // TODO: swap magic numbers with text
    if(trace(ray, hit))
    {
        auto scattered = Ray();
        auto attenuation = vec3<float>();

        if(depth < st->depthMax && hit.material->scatter(ray, hit, attenuation, scattered))
            return hadamard(attenuation, getRayColour(scattered, depth + 1));
        else
            return vec3(0.0f);
    }
    else
    {
        // Sky colour
        auto direction = normalise(ray.direction);
        float t = 0.5f * (direction.y + 1.0f);
        return (1.0f - t) * st->sky_bottom + t * st->sky_top;
    }
}

bool Scene::trace(const Ray &ray, HitData &hit) const
{
    constexpr auto TMIN = 0.001f;
    constexpr auto TMAX = float(0xffffffff);

    bool result = false;
    float closest = TMAX;
    HitData temp{};

    for (const auto &shape : shapes)
    {
        if(shape->hit(ray, TMIN, closest, temp))
        {
            closest = temp.t;
            hit = temp;
            result = true;
        }
    }

    return result;
}
