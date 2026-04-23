/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Sphere
*/

#pragma once

#include "Math/Ameth.hpp"
#include "plugins/IPrimitive.hpp"

#include <optional>
#include <string>
#include <utility>

namespace RayTracer {

class Sphere : public IPrimitive {
public:
    Sphere(Ameth::Vec3D c, double r);

    bool hits(Camera::Ray const &ray) override;
    std::string getName() const override;
    Ameth::Vec3D pointAt(double u, double v) override;

    Ameth::Vec3D center;
    double radius{};

private:
    std::optional<std::pair<double, double>> lineSphereIntersect(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const;
    bool isForwardSurfaceHit(double t0, double t1) const;

    std::string name{"Sphere"};
};

}
