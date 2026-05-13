/*
** EPITECH PROJECT, 2026
** raytracing render
** File description:
**
*/

#include "RaytracingRender.hpp"
#include <iostream>


Ameth::Color RaytracingRender::ComputeTransparency(Ray::HitRecord &oldRec, Ray const &raycast, RayTracer::Scene &scene)
{
    Ray::HitRecord newRec;
    Ray newRay;
    newRay.direction = raycast.direction.normalized();
    newRay.origin = oldRec.point + raycast.direction.normalized() * EPSILON;
    
    if (isRayHitting(scene, newRay, newRec))
        return computeLight(newRec, newRay, scene);
    else
        return _bg;
}

Ameth::Color RaytracingRender::computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene)
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
        // std::cout << "no material found" << std::endl;
        return finalColor;
    }
    if (hit.material->isTransparent()){
        Ameth::Color tmp = hit.material->getColor(finalColor);
        Ameth::Color refractLight = ComputeTransparency(hit, raycast,scene);
        double t = (1 - hit.material->getTransparency());
        refractLight *= t;
        finalColor.r = std::max(tmp.r, refractLight.r);
        finalColor.g = std::max(tmp.g, refractLight.g);
        finalColor.b = std::max(tmp.b, refractLight.b);
        return finalColor;
    }
    return hit.material->getColor(finalColor);
}