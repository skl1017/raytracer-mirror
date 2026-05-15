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
class IRenderer
{
private:
public:
    virtual void renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler) = 0;
    virtual Ameth::Color computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene) = 0;
};
