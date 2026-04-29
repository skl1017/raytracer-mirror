/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#pragma once

#include "Camera/Camera.hpp"
#include "Math/Ameth.hpp"
#include "plugins/IMaterial.hpp"
#include "plugins/IPrimitive.hpp"

#include <memory>
#include <vector>

namespace RayTracer
{
    struct LightSource {
        Ameth::Vec3D position;
        Ameth::Color intensity;
    };

    class Scene {
    public:
        Scene(std::vector<std::unique_ptr<Camera>> cameras,
            std::vector<std::unique_ptr<IPrimitive>> primitives,
            std::vector<std::shared_ptr<IMaterial>> materials = {},
            std::vector<LightSource> lights = {});

        std::vector<std::unique_ptr<Camera>> _cameras;
        std::vector<std::unique_ptr<IPrimitive>> _primitives;
        std::vector<std::shared_ptr<IMaterial>> _materials;
        std::vector<LightSource> _lights;
    };
}
