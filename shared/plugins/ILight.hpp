/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ILight
*/

#pragma once

<<<<<<< HEAD
class ILight
{
private:
    /* data */
public:
    ILight(/* args */) {};
    ~ILight() = default;
=======
#include "Math/Ameth.hpp"
#include "Camera/Camera.hpp"
#include "Ray/Ray.hpp"

class ILight
{
public:
    virtual Ameth::Color getIllumination(Ray::HitRecord &hitRecord) = 0;
>>>>>>> c87a698eeb8270823eaca7aa787d1ec44d6371bc
};
