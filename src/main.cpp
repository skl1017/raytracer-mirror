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
#include "Core/Core.hpp"
#include "Parser/Parser.hpp"

int main(int argc, char **argv)
{
    if (argc < 2){
        return 84;
    }
    RayTracer::Core c(argv[1]);
    if (argc == 3){
        c.run(std::string(argv[2]));
    } else {
        c.run();
    }
    return 0;
}
