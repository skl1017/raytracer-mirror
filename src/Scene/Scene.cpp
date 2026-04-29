/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#include "Scene.hpp"

#include <cmath>

RayTracer::Scene::Scene(std::vector<std::unique_ptr<Camera>> camera,
        std::vector<std::unique_ptr<IPrimitive>> primitives,
        std::vector<std::shared_ptr<IMaterial>> materials,
        std::vector<LightSource> lights)
    :
    _cameras(std::move(camera)),
    _primitives(std::move(primitives)),
    _materials(std::move(materials)),
    _lights(std::move(lights))
{
}