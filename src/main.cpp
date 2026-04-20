/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "Display.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>

int main()
{
    constexpr unsigned width = 1920;
    constexpr unsigned height = 1080;
    constexpr std::string_view outputPath = "output.ppm";

    Display display(width, height, "HDR gradient (hdrTestSample)");
    if (!display.create())
        throw std::runtime_error("Failed to create SFML window or texture");

    while (display.isOpen()) {
        display.pollEvents();
        for (unsigned y = 0; y < height; ++y) {
            for (unsigned x = 0; x < width; ++x) {
                std::size_t const i = std::size_t(y) * width + x;
                display.toDisplaySpace(Display::hdrTestSample(x, y, width, height), i);
            }
        }
        display.update();
    }

    if (!display.savePPM(std::string(outputPath)))
        throw std::runtime_error("Failed to write " + std::string(outputPath));

    return 0;
}
