/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer
{
    Scene::Scene(std::vector<std::unique_ptr<Camera>> cameras,
        std::vector<std::unique_ptr<IPrimitive>> primitives,
        std::vector<std::shared_ptr<IMaterial>> materials,
        std::vector<std::unique_ptr<ILight>> lights)
    : _materials(std::move(materials)),
        _cameras(std::move(cameras)),
        _primitives(std::move(primitives)),
        _lights(std::move(lights))
{
}
}
