/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "Camera/Camera.hpp"
#include "Display/Display.hpp"
#include "Math/Ameth.hpp"
#include "Primitives/Sphere/Sphere.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

int main()
{
    constexpr unsigned LENGTH = 1000;
    constexpr unsigned WIDTH = 1000;
    constexpr std::string_view outputPath = "output.ppm";
    constexpr double pinholeZ = 1000.0;

    Camera cam(LENGTH, WIDTH,
        Ameth::Vector3D(static_cast<double>(LENGTH), 0.0, 0.0),
        Ameth::Vector3D(0.0, static_cast<double>(WIDTH), 0.0),
        pinholeZ);
    RayTracer::Sphere sphere(Ameth::Vector3D(0.0, 200.0, -40.0), 39.9);

    for (unsigned x = 0; x < LENGTH; ++x) {
        for (unsigned y = 0; y < WIDTH; ++y) {
            double u = static_cast<double>(x) / static_cast<double>(LENGTH);
            double v = static_cast<double>(y) / static_cast<double>(WIDTH);
            Camera::Ray r = cam.ray(u, v);
            std::size_t i = y * LENGTH + x;
            if (sphere.hits(r)) {
                cam.getHDRImage()[i] = Ameth::Vector3D(1.0, 0.0, 0.0);
            } else {
                cam.getHDRImage()[i] = Ameth::Vector3D(0.0, 0.0, 1.0);
            }
        }
    }

    Display display(LENGTH, WIDTH, "raytracer");
    if (!display.create())
        throw std::runtime_error("Failed to create SFML window or texture");

    while (display.isOpen()) {
        display.pollEvents();
        display.update(cam.getHDRImage());
    }

    if (!display.savePPM(std::string(outputPath)))
        throw std::runtime_error("Failed to write " + std::string(outputPath));
    return 0;
}
