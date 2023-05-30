cmake_minimum_required(VERSION 3.23)
project(Raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(Raytracer main.cpp Raytracer.cpp Raytracer.h Utils.cpp Utils.h Material.cpp Sphere.cpp Sphere.h Camera.cpp Camera.h Scene.cpp Scene.h Shared.h)
