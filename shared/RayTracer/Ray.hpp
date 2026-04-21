/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DLLoader
*/

#pragma once

#include "Math/Point3D.hpp"
#include "Math/Vector3D.hpp"

namespace RayTracer
{
    class Ray
    {
    private:
        Math::Point3D<double> _origin;
        Math::Vector3D<double> _direction;
    public:
        Ray(Math::Point3D<double> origin, Math::Vector3D<double> direction) : _origin(origin), _direction(direction) {};
        ~Ray() = default;

        Math::Point3D<double> &getOrigin() { return _origin;};
        Math::Vector3D<double> &getDirection() { return _direction;};
    };
}
