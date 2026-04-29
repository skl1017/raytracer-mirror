/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#include "Core.hpp"
#include "Camera/Camera.hpp"
#include "Display/Display.hpp"
#include "Parser/Parser.hpp"
#include "Primitives/Sphere/Sphere.hpp"
#include "Renderer/Renderer.hpp"
#include "plugins/IPrimitive.hpp"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace RayTracer
{
    // Core::Core(const std::string &file)
    //     : _pluginManager({
    //           DLLoader<IPrimitive>(),
    //       }),
    //       _scene([&]() {
    //           Parser parser(_pluginManager);
    //           return parser.loadFile(file);
    //       }())
    // {
    // }

    Core::Core(Scene scene)
        : _pluginManager({
              DLLoader<IPrimitive>(),
          }),
          _scene(std::move(scene))
    {
    }

    Core Core::createDemo()
    {
        constexpr double fovV = 2.0 * std::atan(0.5);
        constexpr unsigned width = 1920;
        constexpr unsigned height = 1080;

        std::vector<std::unique_ptr<Camera>> cameras;
        cameras.push_back(std::make_unique<Camera>(Ameth::Vec3D(0.0, 200, -350), Ameth::Quaternion::identity(), fovV, width, height));
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        primitives.push_back(std::make_unique<RayTracer::Sphere>(Ameth::Vec3D(0.0, 200.0, 0.0), 39.9));
        primitives.push_back(std::make_unique<RayTracer::Sphere>(Ameth::Vec3D(-130.0, 190.0, 50.0), 28.0));
        primitives.push_back(std::make_unique<RayTracer::Sphere>(Ameth::Vec3D(125.0, 210.0, 35.0), 32.0));
        primitives.push_back(std::make_unique<RayTracer::Sphere>(Ameth::Vec3D(-55.0, 175.0, 95.0), 18.0));
        primitives.push_back(std::make_unique<RayTracer::Sphere>(Ameth::Vec3D(70.0, 230.0, 75.0), 22.0));
        primitives.push_back(std::make_unique<RayTracer::Sphere>(Ameth::Vec3D(0.0, 255.0, -70.0), 24.0));

        std::vector<std::shared_ptr<IMaterial>> materials;
        std::vector<LightSource> lights;
        lights.push_back({Ameth::Vec3D(300.0, 400.0, -200.0), Ameth::Color(1.0, 1.0, 1.0)});

        Scene scene(std::move(cameras), std::move(primitives), std::move(materials), std::move(lights));
        return Core(std::move(scene));
    }

    int Core::run(std::string_view outputPath)
    {
        Renderer::renderNormals(_scene);

        for (size_t index = 0; index < _scene._cameras.size(); ++index) {
            Display display(_scene._cameras[index]->imageWidth(), _scene._cameras[index]->imageHeight(), "raytracer");
            if (!display.create())
                throw std::runtime_error("Failed to create SFML window or texture");
            while (display.isOpen()) {
                display.pollEvents();
                display.update(_scene._cameras[index]->getHDRImage());
            }
            if (!display.savePPM(std::string(outputPath)))
                throw std::runtime_error("Failed to write " + std::string(outputPath));
        }
        return 0;
    }
}
