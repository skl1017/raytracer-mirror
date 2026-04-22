/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Sphere
*/

#pragma once

#include "Math/Ameth.hpp"
#include "plugins/IPrimitive.hpp"

#include <string>

namespace RayTracer {

class Sphere : public IPrimitive {
public:
    Sphere(Ameth::Vector3D c, double r)
        : center(c),
          radius(r)
    {
    }

    bool hits(Camera::Ray const &ray) override
    {
        Ameth::Vector3D const &dir = ray.direction;
        Ameth::Vector3D const &o = ray.origin;
        Ameth::Vector3D oc(o.x - center.x, o.y - center.y, o.z - center.z);

        double a = dir.dot(dir);
        double b = 2.0 * oc.dot(dir);
        double c = oc.dot(oc) - radius * radius;

        return (b * b - 4.0 * a * c) > 0.0;
    }

    std::string getName() const override { return name; }

    Ameth::Vector3D pointAt(double /*u*/, double /*v*/) override { return center; }

    Ameth::Vector3D center;
    double radius{};

private:
    std::string name{"sphere"};
};

} // namespace RayTracer
