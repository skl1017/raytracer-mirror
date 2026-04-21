/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DLLoader
*/

#pragma once

#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace RayTracer {
    class Rectangle3D : IPrimitive {
        public:
            Rectangle3D() : origin(0, 0, 0), bottom_side(1, 0, 0), left_side(0, 1, 0) {};
            Math::Point3D<double> pointAt(double u, double v)
            {
                return Math::Point3D<double>(u, v, 0);
            };
            Math::Point3D<double> origin;
            Math::Vector3D<double> bottom_side;
            Math::Vector3D<double> left_side;
    };
}