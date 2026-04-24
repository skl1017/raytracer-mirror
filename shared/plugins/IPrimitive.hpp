/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** IPrimitive
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Ray/Ray.hpp"

#include <string>

enum PLUGIN {
    PRIMITIVE,
    MATERIAL,
    LIGHT
};

class IPrimitive {
public:
    virtual bool hit(Ray const &ray, Ray::HitRecord &rec) const = 0;
    virtual std::string getName() const = 0;
    virtual Ameth::Vec3D pointAt(double u, double v) const = 0;
    virtual ~IPrimitive() = default;
};
