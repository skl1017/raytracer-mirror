/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ILight
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Camera/Camera.hpp"
#include "Ray/Ray.hpp"

class ILight
{
public:
    virtual Ameth::Color getIllumination(Ray::HitRecord &hitRecord) = 0;
};
