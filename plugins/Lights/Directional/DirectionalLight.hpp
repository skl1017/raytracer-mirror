/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DirectionalLight
*/

#pragma once
#include "plugins/ILight.hpp"

class DirectionalLight : public ILight
{
public:
    DirectionalLight(Ameth::Vec3D direction, Ameth::Color lightColor) :
        _direction(direction), _LightColor(lightColor) {};
    ~DirectionalLight() = default;
    Ameth::Color getIllumination(Ray::HitRecord &hitRecord) override;
protected:
    Ameth::Vec3D _direction;
    Ameth::Color _LightColor;
};
