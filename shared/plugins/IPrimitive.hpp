/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** IPrimitive
*/

#pragma once

#include "Camera/Camera.hpp"
#include "Math/Ameth.hpp"

#include <string>

enum PLUGIN {
    PRIMITIVE,
    MATERIAL,
    LIGHT
};

class IPrimitive {
public:
    virtual bool hit(Camera::Ray const &ray, Camera::HitRecord &rec) const = 0;
    virtual std::string getName() const = 0;
    virtual Ameth::Vec3D pointAt(double u, double v) const = 0;
    virtual ~IPrimitive() = default;
};
