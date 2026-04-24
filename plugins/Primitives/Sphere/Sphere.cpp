/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "plugins/IPrimitive.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <utility>

namespace RayTracer {

Sphere::Sphere(Ameth::Vec3D c, double r, std::shared_ptr<IMaterial> material)
    : center(c),
      radius(std::max(0.0, r)),
      _material(std::move(material))
{
}

std::optional<std::pair<double, double>> Sphere::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vec3D const originToCenter = origin - center;
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

void Sphere::fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const
{
    rec.t = t;
    rec.point = ray.at(t);
    rec.normal = (rec.point - center) * (1.0 / radius);
    rec.normal = rec.normal.normalized();
    double const x = 0.5 + std::atan2(rec.normal.x, rec.normal.z) / (2.0 * std::numbers::pi);
    rec.u = x - std::floor(x);
    rec.v = 0.5 - std::asin(std::clamp(rec.normal.y, -1.0, 1.0)) / std::numbers::pi;
    rec.material = _material;
}

std::string Sphere::getName() const
{
    return name;
}

Ameth::Vec3D Sphere::pointAt(double u, double v) const
{
    (void)u;
    (void)v;
    return center;
}

} // namespace RayTracer

extern "C" IPrimitive *create()
{
    return new RayTracer::Sphere(Ameth::Vec3D(0.0, 0.0, 0.0), 1.0, nullptr);
}

extern "C" PLUGIN getLibType()
{
    return PRIMITIVE;
}
