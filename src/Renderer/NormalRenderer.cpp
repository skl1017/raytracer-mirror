/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#include "Renderer/NormalRenderer.hpp"
#include "Scene/Scene.hpp"
#include "../../plugins/Materials/FlatColor/flatColor.hpp"

#include <cstddef>
#include <limits>
#include <iostream>
#include <algorithm>

Ameth::Color NormalRenderer::computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene)
{
    (void)scene;
    Ameth::Vec3D n = hit.normal;
    return Ameth::Color(0.5 * (n.x + 1.0), 0.5 * (n.y + 1.0), 0.5 * (n.z + 1.0));
}
