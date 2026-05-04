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
#include "plugins/ILight.hpp"
#include <memory>
#include <vector>

namespace RayTracer
{
    class Scene {
        public:
            Scene(std::vector<std::unique_ptr<Camera>> cameras,
                std::vector<std::unique_ptr<IPrimitive>> primitives,
                std::vector<std::shared_ptr<IMaterial>> materials = {},
                std::vector<std::unique_ptr<ILight>> lights = {});

            std::vector<std::shared_ptr<IMaterial>> _materials;
            std::vector<std::unique_ptr<Camera>> _cameras;
            std::vector<std::unique_ptr<IPrimitive>> _primitives;
            std::vector<std::unique_ptr<ILight>> _lights;
    };
}
