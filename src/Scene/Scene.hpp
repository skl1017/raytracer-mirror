/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#pragma once
#include "plugins/IPrimitive.hpp"
#include <memory>
namespace RayTracer
{
    class Scene {
        public:
            Scene(std::vector<std::unique_ptr<IPrimitive>> primitives);

        private:
            std::vector<std::unique_ptr<IPrimitive>> _primitives;
    };
}
