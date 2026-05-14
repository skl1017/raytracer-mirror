/*
** EPITECH PROJECT, 2026
** raytracing render
** File description:
**
*/

#include "RaytracingRender.hpp"
#include <iostream>

// Ameth::Vec3D refract( const Ameth::Vec3D &incoming, const Ameth::Vec3D &normal,
//     double indOfRefrac)
// {
//     Ameth::Vec3D I = incoming.normalized();
//     Ameth::Vec3D N = normal.normalized();
//     double cosi = std::clamp(I.dot(N), -1.0, 1.0);
//     double refracAir = 1.0;
//     double refracMat = indOfRefrac;

//     if (cosi > 0) {
//         std::swap(refracAir, refracMat);
//         N *= -1;
//     } else {
//         cosi = -cosi;
//     }
//     double eta = refracAir / refracMat;
//     double internal = 1 - eta * eta * (1 - cosi * cosi);
//     if (internal < 0)
//         return I - N * 2 * I.dot(N);
//     return I * eta + N * (eta * cosi - std::sqrt(internal));
// }


Ameth::Color RaytracingRender::ComputeTransparency(Ray::HitRecord &oldRec,
    Ray const &raycast, RayTracer::Scene &scene)
{
    Ray::HitRecord newRec;
    Ray newRay;
    newRay.direction = raycast.direction.normalized();
    newRay.origin = oldRec.point + newRay.direction * EPSILON;

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
        lightColor = scene._lights[i]->getIllumination(hit, raycast);
        finalColor.r = std::max(finalColor.r, lightColor.r);
        finalColor.g = std::max(finalColor.g, lightColor.g);
        finalColor.b = std::max(finalColor.b, lightColor.b);
    }
    if (!hit.material){
        return finalColor;
    }
    if (hit.material->isTransparent()){
        Ameth::Color tmp = hit.material->getColor(finalColor);
        Ameth::Color refractLight = ComputeTransparency(hit, raycast,scene);
        double t = hit.material->getTransparency();

        refractLight *= t;
        tmp *= 1 - t;
        finalColor.r = tmp.r + refractLight.r;
        finalColor.g = tmp.g + refractLight.g;
        finalColor.b = tmp.b + refractLight.b;
        return finalColor;
    }
    return hit.material->getColor(finalColor);
}