/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

Ameth::Color DirectionalLight::getIllumination(Ray::HitRecord &hitRecord)
{
    Ameth::Color illumination = _LightColor;
    Ameth::Vec3D incidentLight = Ameth::Vec3D(0, 0, 0) - _direction;
    double ambient = 0.1;
    double angle = hitRecord.normal.dot(incidentLight.normalized());
    double intensity = ambient + std::max(0.0, angle);

    return illumination * intensity;
}