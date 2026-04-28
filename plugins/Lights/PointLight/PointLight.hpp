/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** PointLight
*/

#pragma once
#include "plugins/ILight.hpp"

namespace RayTracer {

    class PointLight : public ILight
    {
public:
    PointLight(Ameth::Vec3D position, Ameth::Color lightColor) :
    _position(position), _LightColor(lightColor) {};
    ~PointLight() = default;
    Ameth::Color getIllumination(Ray::HitRecord &hitRecord) override;
    protected:
    Ameth::Vec3D _position;
    Ameth::Color _LightColor;
};
}
