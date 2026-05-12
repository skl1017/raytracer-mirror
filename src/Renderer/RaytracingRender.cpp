/*
** EPITECH PROJECT, 2026
** raytracing render
** File description:
** 
*/

#include "RaytracingRender.hpp"

Ameth::Color RaytracingRender::computeLight(Ray::HitRecord &hit, RayTracer::Scene &scene)
{
    Ameth::Color lightColor(0, 0, 0);
    Ameth::Color finalColor(0, 0, 0);

    for (size_t i = 0; i < scene._lights.size(); i++) {
        lightColor = scene._lights[i]->getIllumination(hit);

        finalColor.r = std::max(finalColor.r, lightColor.r);
        finalColor.g = std::max(finalColor.g, lightColor.g);
        finalColor.b = std::max(finalColor.b, lightColor.b);
    }
    if (!hit.material){
        return finalColor;
    }
    if (hit.material->isTransparent()){
        Ameth::Color tmp = hit.material->getColor(finalColor);
        double t = (1 - hit.material->getTransparency());
        
        finalColor.r = std::max(tmp.r, _bg.r * t);
        finalColor.g = std::max(tmp.g, _bg.g * t);
        finalColor.b = std::max(tmp.b, _bg.b * t);
        return finalColor;
    }
    return hit.material->getColor(finalColor);
}