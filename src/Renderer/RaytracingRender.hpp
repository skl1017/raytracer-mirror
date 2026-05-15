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

    Ameth::Color computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene) override;
private:
    Ameth::Color ComputeTransparency(Ray::HitRecord &oldRec, Ray const &raycast, RayTracer::Scene &scene);
    Ameth::Color handleLight(RayTracer::Scene &scene, Ray::HitRecord &hit, Ray const &raycast);
};
