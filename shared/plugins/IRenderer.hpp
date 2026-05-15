/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** IRenderer
*/

#pragma once
#include "Math/Ameth.hpp"
#include "Renderer/ParallelImageScheduler.hpp"
#include "Scene/Scene.hpp"
#include <cstddef>

class IRenderer
{
private:
public:
    static constexpr std::size_t kMaxRayDepth = 5;

    virtual void renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler) = 0;
    virtual Ameth::Color computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene, std::size_t depth = kMaxRayDepth) = 0;
};
