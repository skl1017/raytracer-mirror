/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include <cmath>
#include <utility>

namespace RayTracer {

Sphere::Sphere(Ameth::Vector3D c, double r)
    : center(c),
      radius(r)
{
}

std::optional<std::pair<double, double>> Sphere::lineSphereIntersect(Ameth::Vector3D const &origin, Ameth::Vector3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vector3D const originToCenter = origin - center;
    double const quadA = dir.dot(dir);
    double const quadB = 2.0 * originToCenter.dot(dir);
    double const quadC = originToCenter.dot(originToCenter) - radius * radius;
    double const discriminant = quadB * quadB - 4.0 * quadA * quadC;
    if (discriminant < 0.0)
        return std::nullopt;
    double const sqrtDisc = std::sqrt(discriminant);
    double const tMinusSqrt = (-quadB - sqrtDisc) / (2.0 * quadA);
    double const tPlusSqrt = (-quadB + sqrtDisc) / (2.0 * quadA);
    return std::make_pair(tMinusSqrt, tPlusSqrt);
}

bool Sphere::isForwardSurfaceHit(double t0, double t1) const
{
    double tFirst = -1.0;
    if (t0 > 0.0)
        tFirst = t0;
    if (t1 > 0.0 && (tFirst < 0.0 || t1 < tFirst))
        tFirst = t1;
    return tFirst > 0.0;
}

bool Sphere::hits(Camera::Ray const &ray)
{
    std::optional<std::pair<double, double>> intersects = lineSphereIntersect(ray.origin, ray.direction);
    if (!intersects)
        return false;
    return isForwardSurfaceHit(intersects->first, intersects->second);
}

std::string Sphere::getName() const
{
    return name;
}

Ameth::Vector3D Sphere::pointAt(double /*u*/, double /*v*/)
{
    return center;
}

} // namespace RayTracer
