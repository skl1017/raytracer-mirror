/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer
{
    Scene::Scene(std::vector<std::unique_ptr<IPrimitive>> primitives):_primitives(std::move(primitives))
    {

    }
}
