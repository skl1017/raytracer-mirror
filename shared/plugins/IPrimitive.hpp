/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** IPrimitive
*/

#pragma once

#include <string>

#include "Camera/Camera.hpp"
#include "Math/Ameth.hpp"

enum PLUGIN {
    PRIMITIVE,
    MATERIAL,
    LIGHT
};

class IPrimitive {
public:
    virtual std::string getName() const = 0;
    virtual Ameth::Vector3D pointAt(double u, double v) = 0;
    virtual bool hits(Camera::Ray const &ray) = 0;
    virtual ~IPrimitive() = default;
};
