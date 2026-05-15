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

Ameth::Vec3D reflect(const Ameth::Vec3D &I_in, const Ameth::Vec3D &N_in)
{
    Ameth::Vec3D I = I_in.normalized();
    Ameth::Vec3D N = N_in.normalized();

    return I - N * 2.0 * I.dot(N);
}


Ameth::Color RaytracingRender::ComputeTransparency(Ray::HitRecord &oldRec,
    Ray const &raycast, RayTracer::Scene &scene, std::size_t depth)
{
    if (depth == 0)
        return _bg;
    Ray::HitRecord newRec;
    Ray newRay;
    newRay.direction = raycast.direction.normalized();
    newRay.origin = oldRec.point + newRay.direction * EPSILON;

    if (isRayHitting(scene, newRay, newRec))
        return computeLight(newRec, newRay, scene, depth - 1);
    return _bg;
}

Ameth::Color RaytracingRender::handleLight(RayTracer::Scene &scene, Ray::HitRecord &hit, Ray const &raycast)
{
    Ray::HitRecord lightRecord = {};
    Ameth::Color lightColor(0, 0, 0);
    Ameth::Color finalColor(0, 0, 0);
    Ray lightRay;

    for (size_t i = 0; i < scene._lights.size(); i++) {
        lightColor = scene._lights[i]->getIllumination(hit, raycast);
        lightRay.direction = scene._lights[i]->getDirectVector(hit);
        lightRay.origin = hit.point + hit.normal * EPSILON;
        if (isRayHitting(scene, lightRay, lightRecord, 1)) {
            if (lightRay.direction.length() > (lightRecord.point - hit.point).length()) {
                lightColor = {0, 0, 0};
            }
        }
        finalColor += lightColor;
    }
    return finalColor;
}

Ameth::Color RaytracingRender::computeLight(Ray::HitRecord &hit, Ray const &raycast, RayTracer::Scene &scene, std::size_t depth)
{
    Ameth::Color finalColor(0, 0, 0);

    if (depth == 0)
        return _bg;
    if (!hit.material)
        return finalColor;
    finalColor = handleLight(scene, hit, raycast);
    if (hit.material->isTransparent()) {
        Ameth::Color tmp = hit.material->getColor(finalColor);
        Ameth::Color refractLight = ComputeTransparency(hit, raycast, scene, depth - 1);
        double t = hit.material->getTransparency();
        refractLight *= t;
        tmp *= 1 - t;
        finalColor.r = tmp.r + refractLight.r;
        finalColor.g = tmp.g + refractLight.g;
        finalColor.b = tmp.b + refractLight.b;
        return finalColor;
    }
    if (hit.material->isReflecting()) {
        Ray reflected;
        reflected.direction = reflect(raycast.direction, hit.normal);
        reflected.origin = hit.point + hit.normal * EPSILON;
        Ray::HitRecord reflectRecord;
        double r = hit.material->getReflection();

        if (!isRayHitting(scene, reflected, reflectRecord))
            return hit.material->getColor(finalColor) * (1 - r) + _bg * r;
        return hit.material->getColor(finalColor) * (1 - r)
            + computeLight(reflectRecord, reflected, scene, depth - 1) * r;
    }
    return hit.material->getColor(finalColor);
}
