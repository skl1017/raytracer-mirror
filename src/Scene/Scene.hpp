/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#pragma once
#include "plugins/IPrimitive.hpp"
#include "plugins/ILight.hpp"
#include <memory>
#include <vector>
namespace RayTracer
{
    class Scene {
        public:
            Scene(std::vector<std::unique_ptr<IPrimitive>>, std::vector<std::unique_ptr<ILight>>);

        private:
            std::vector<std::unique_ptr<IPrimitive>> _primitives;
            std::vector<std::unique_ptr<ILight>> _lights;
    };
}
