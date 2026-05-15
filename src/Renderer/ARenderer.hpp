/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ARendere
*/

#pragma once
#include "plugins/IRenderer.hpp"
#define EPSILON 1e-4

class ARenderer : public IRenderer
{
protected:
    Ameth::Color _bg;
    bool isRayHitting(RayTracer::Scene &scene, Ray const &raycast, Ray::HitRecord &rec);
    bool isRayHitting(RayTracer::Scene &scene, Ray const &raycast, Ray::HitRecord &rec, std::size_t depth);
public:
    ARenderer(Ameth::Color bgColor) : _bg(bgColor) {};
    ~ARenderer() {};
    void renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler) override;
};
