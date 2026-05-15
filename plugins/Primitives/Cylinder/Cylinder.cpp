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
#include <cmath>
#include <memory>
#include <utility>

namespace RayTracer {

Cylinder::Cylinder(Ameth::Vec3D c, double radius, double height, Ameth::Vec3D rotation, std::shared_ptr<IMaterial> material)
    : APrimitive(material, rotation),
      center(c),
      radius(std::max(0.0, radius)),
      height(height)
{
}

std::optional<std::pair<double, double>> Cylinder::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    Ameth::Vec3D const u = _axis.normalized();
    Ameth::Vec3D const originToCenter = origin - center;
    double const DirDotAxis = dir.dot(u);
    double const OcDotAxis = originToCenter.dot(u);
    Ameth::Vec3D const dirProjection = dir - u * DirDotAxis;
    Ameth::Vec3D const ocProjection = originToCenter - u * OcDotAxis;
    double const quadA = dirProjection.dot(dirProjection);
    double const quadB = 2 * dirProjection.dot(ocProjection);
    double const quadC = ocProjection.dot(ocProjection) - std::pow(radius, 2);

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
    rec.point = ray.at(t);
    Ameth::Vec3D const u = _axis.normalized();
    Ameth::Vec3D const v = rec.point - center;
    rec.normal = (v - u * v.dot(u)).normalized();
    rec.material = _material;
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
        return std::make_unique<RayTracer::Cylinder>(
            cylinderPayload.position,
            cylinderPayload.radius,
            cylinderPayload.height,
            cylinderPayload.rotation,
            std::move(cylinderPayload.material));
    };
    factory.add("cylinder", f);
}
