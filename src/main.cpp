/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "Camera/Camera.hpp"
#include "Display/Display.hpp"
#include "Math/Ameth.hpp"
#include "Renderer/Renderer.hpp"
#include "Primitives/Sphere/Sphere.hpp"

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

int main()
{
    constexpr std::string_view outputPath = "output.ppm";
    constexpr double fovV = 2.0 * std::atan(0.5);
    constexpr unsigned WIDTH = 1920;
    constexpr unsigned HEIGHT = 1080;

    Camera cam(Ameth::Vec3D(0.0, 200, -350), Ameth::Quaternion::identity(), fovV, WIDTH, HEIGHT);
    RayTracer::Sphere sphere(Ameth::Vec3D(0.0, 200.0, 0.0), 39.9);

    for (unsigned x = 0; x < WIDTH; ++x) {
        for (unsigned y = 0; y < HEIGHT; ++y) {
            double const su = (static_cast<double>(x) + 0.5) / static_cast<double>(WIDTH);
            double const sv = (static_cast<double>(y) + 0.5) / static_cast<double>(HEIGHT);
            Ray const r = cam.ray(su, sv);
            std::size_t const i = y * WIDTH + x;
            Ray::HitRecord rec{};
            if (sphere.hit(r, rec)) {
                cam.getHDRImage()[i] = Renderer::normalToColor(rec.normal);
            } else {
                cam.getHDRImage()[i] = Ameth::Color(0.0, 0.0, 0.2);
            }
        }
    }

    Display display(WIDTH, HEIGHT, "raytracer");
    if (!display.create())
        throw std::runtime_error("Failed to create SFML window or texture");

    //std::vector<Ameth::Vec3D> hdrImage = display.loadHDRTestSample(WIDTH, HEIGHT);
    while (display.isOpen()) {
        display.pollEvents();
        //display.update(hdrImage);
        display.update(cam.getHDRImage());
    }

    if (!display.savePPM(std::string(outputPath)))
        throw std::runtime_error("Failed to write " + std::string(outputPath));
    return 0;
}
