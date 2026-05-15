/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#pragma once

#include "Bvh/Bvh.hpp"
#include "Camera/Camera.hpp"
#include "Math/Ameth.hpp"
#include "plugins/IMaterial.hpp"
#include "plugins/IPrimitive.hpp"
#include "plugins/ILight.hpp"
#include <memory>
#include <vector>
#include <map>

namespace RayTracer
{
    class Scene {
        public:
            Scene(std::vector<std::unique_ptr<Camera>> cameras,
                std::vector<std::unique_ptr<IPrimitive>> primitives,
                std::map<std::string, std::shared_ptr<IMaterial>> materials = {},
                std::vector<std::unique_ptr<ILight>> lights = {});

            std::map<std::string, std::shared_ptr<IMaterial>> _materials;
            std::vector<std::unique_ptr<Camera>> _cameras;
            std::vector<std::unique_ptr<IPrimitive>> _primitives;
            std::vector<std::unique_ptr<ILight>> _lights;
            Bvh _bvh;
    };
}
