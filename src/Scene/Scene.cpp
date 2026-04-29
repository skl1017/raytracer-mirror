/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer
{
    Scene::Scene(std::vector<std::unique_ptr<IPrimitive>> primitives, std::vector<std::unique_ptr<ILight>> lights)
    :_primitives(std::move(primitives))
    , _lights(std::move(lights))
    {

    }
}
