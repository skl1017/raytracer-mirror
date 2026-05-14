/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Cone
*/

#include "Cone.hpp"
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

Cone::Cone(Ameth::Vec3D c, Ameth::Vec3D rotation, std::shared_ptr<IMaterial> material): APrimitive(material), center(c),
      rotation(rotation) {}

Ameth::Vec3D getProjection(Ameth::Vec3D vecteur, Ameth::Vec3D axis)
{
   return vecteur - axis * vecteur.dot(axis);
}

std::optional<std::pair<double, double>> Cone::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vec3D const originToCenter = origin - center;
    double const quadA = std::pow(dir.x, 2) + std::pow(dir.y, 2) - std::pow(dir.z, 2);
    double const quadB = 2 * ((originToCenter.x * dir.x) + (originToCenter.y * dir.y) - (originToCenter.z * dir.z));
    double const quadC = std::pow(originToCenter.x, 2) + std::pow(originToCenter.y, 2) - std::pow(originToCenter.z, 2);
    double const discriminant = std::pow(quadB, 2) - (4 * quadA * quadC);
    if (discriminant < 0.0)
        return std::nullopt;
    double const sqrtDisc = std::sqrt(discriminant);
    double const tMinusSqrt = (-quadB - sqrtDisc) / (2.0 * quadA);
    double const tPlusSqrt = (-quadB + sqrtDisc) / (2.0 * quadA);
    return std::make_pair(tMinusSqrt, tPlusSqrt);
}

void Cone::fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const
{
    rec.t = t;
    rec.point = ray.at((t));
    Ameth::Vec3D const originToCenter = rec.point - center;
    Ameth::Vec3D normal(
        originToCenter.x,
        originToCenter.y,
        -std::sqrt(std::pow(originToCenter.x, 2) + std::pow(originToCenter.y, 2))
    );
    rec.normal = normal.normalized();
    if (ray.direction.dot(rec.normal) > 0)
        rec.normal = rec.normal * -1;
}

std::string Cone::getName() const
{
    return name;
}

Ameth::Vec3D Cone::pointAt(double u, double v) const
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
        auto const conePayload = std::get<RayTracer::PluginFactory::cone_payload_t>(p);
        return std::make_unique<RayTracer::Cone>(conePayload.position, conePayload.rotation, std::move(conePayload.material));
    };
    factory.add("cone", f);
}
