/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "Ameth.hpp"
#include "Display.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

int main()
{
    constexpr unsigned width = 1920;
    constexpr unsigned height = 1080;
    constexpr std::string_view outputPath = "output.ppm";

    std::vector<Ameth::Vector3D> hdrImage(width * height, {0.0, 0.0, 0.0});

    Display display(width, height, "HDR gradient (hdrTestSample)");
    if (!display.create())
        throw std::runtime_error("Failed to create SFML window or texture");

    display.loadHDRTestSample(hdrImage);
    while (display.isOpen()) {
        display.pollEvents();
        display.update(hdrImage);
    }

    if (!display.savePPM(std::string(outputPath)))
        throw std::runtime_error("Failed to write " + std::string(outputPath));
    return 0;
}
