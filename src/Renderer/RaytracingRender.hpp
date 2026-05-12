/*
** EPITECH PROJECT, 2026
** raytracing render
** File description:
** 
*/

#pragma once
#include "ARenderer.hpp"

class RaytracingRender : public ARenderer
{
public:
    RaytracingRender(Ameth::Color bgColor) : ARenderer(bgColor) {};
    ~RaytracingRender() {};

    Ameth::Color computeLight(Ray::HitRecord &hit, RayTracer::Scene &scene) override;
};
