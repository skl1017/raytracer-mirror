/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ARendere
*/

#pragma once
#include "plugins/IRenderer.hpp"

class ARenderer : public IRenderer
{
protected:
    Ameth::Color _bg;
public:
    ARenderer(Ameth::Color bgColor) : _bg(bgColor) {};
    ~ARenderer() {};
    void renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler) override;
};
