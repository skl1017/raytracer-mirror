/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include <iostream>

Ameth::Color PointLight::getIllumination(Ray::HitRecord &hitRecord)
{
    Ameth::Color illumination = _LightColor;
    Ameth::Vec3D incidentLight = (_position - hitRecord.point).normalized();

    double ambient = 0.1;
    double angle = hitRecord.normal.dot(incidentLight);
    double intensity = ambient + std::max(0.0, angle);
    
    std::cout << "angle : " << angle << " intenisity : " << intensity << std::endl;
    illumination.r *= intensity;
    illumination.g *= intensity;
    illumination.b *= intensity;
    return illumination;
}