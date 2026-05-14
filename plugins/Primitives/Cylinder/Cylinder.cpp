/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "Math/Ameth.hpp"
#include "plugins/IPrimitive.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include <algorithm>
#include <cmath>
#include <memory>
#include <iostream>
#include <numbers>
#include <utility>

namespace RayTracer {

Cylinder::Cylinder(Ameth::Vec3D c, double r, std::shared_ptr<IMaterial> material): APrimitive(material), center(c),
      radius(std::max(0.0, r)){}

std::optional<std::pair<double, double>> Cylinder::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vec3D const originToCenter = origin - center;
    double const quadA = std::pow(dir.x, 2) + std::pow(dir.y, 2);
    double const quadB = 2 * ((originToCenter.x * dir.x) + (originToCenter.y * dir.y));
    double const quadC = std::pow(originToCenter.x, 2) + std::pow(originToCenter.y, 2) - std::pow(radius, 2);
    double const discriminant = std::pow(quadB, 2) - (4 * quadA * quadC);
    if (discriminant < 0.0)
        return std::nullopt;
    double const sqrtDisc = std::sqrt(discriminant);
    double const tMinusSqrt = (-quadB - sqrtDisc) / (2.0 * quadA);
    double const tPlusSqrt = (-quadB + sqrtDisc) / (2.0 * quadA);
    return std::make_pair(tMinusSqrt, tPlusSqrt);
}

void Cylinder::fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const
{
    rec.t = t;
    rec.point = ray.at((t));
    Ameth::Vec3D normal(rec.point.x - center.x,rec.point.y - center.y,0);
    rec.normal = normal.normalized();
    if (ray.direction.dot(rec.normal) > 0)
        rec.normal = rec.normal * -1;
}

std::string Cylinder::getName() const
{
    return name;
}

Ameth::Vec3D Cylinder::pointAt(double u, double v) const
{
    (void)u;
    (void)v;
    return center;
}
} // namespace RayTracer

extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
    RayTracer::PluginFactory::iPrimitiveCreateFunction const f
        = [](RayTracer::PluginFactory::primitivePayload const &p) -> std::unique_ptr<IPrimitive> {
        auto const cylinderPayload = std::get<RayTracer::PluginFactory::cylinder_payload_t>(p);
        return std::make_unique<RayTracer::Cylinder>(cylinderPayload.position, cylinderPayload.r, std::move(cylinderPayload.material));
    };
    factory.add("cylinder", f);
}

extern "C" IPrimitive *create()
{
    return new RayTracer::Cylinder(Ameth::Vec3D(0.0, 0.0, 0.0), 1.0, nullptr);
}

extern "C" PLUGIN getLibType()
{
    return PRIMITIVE;
}
