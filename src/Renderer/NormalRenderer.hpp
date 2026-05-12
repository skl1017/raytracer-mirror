/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Ray/Ray.hpp"
#include "plugins/IRenderer.hpp"
#include "ARenderer.hpp"

namespace RayTracer {
    class Scene;
}

class NormalRenderer : public ARenderer
{
public:
    NormalRenderer(Ameth::Color bgColor) : ARenderer(bgColor) {};
    ~NormalRenderer() = default;
    Ameth::Color computeLight(Ray::HitRecord &hit, RayTracer::Scene &scene) override;
};
