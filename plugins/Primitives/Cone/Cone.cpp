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
#include <cmath>
#include <memory>
#include <utility>

namespace RayTracer {

Cone::Cone(Ameth::Vec3D c, Ameth::Vec3D rotation, double angle, std::shared_ptr<IMaterial> material): APrimitive(material, rotation), center(c),
      rotation(rotation), angle(angle) {};

Ameth::Vec3D getProjection(Ameth::Vec3D vecteur, Ameth::Vec3D axis)
{
   return vecteur - axis * vecteur.dot(axis);
}

std::optional<std::pair<double, double>> Cone::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vec3D const originToCenter = origin - center;
    double const dirDotAxis = dir.dot(axis);
    double const ocDotAxis = originToCenter.dot(axis);
    double const dirDotOc = dir.dot(originToCenter);
    double const OcDotOC = originToCenter.dot(originToCenter);
    double const cosAngleSquare = std::pow(std::cos(angle), 2);
    double const quadA = std::pow(dirDotAxis, 2) - cosAngleSquare;
    double const quadB = 2.0 * (dirDotAxis * ocDotAxis - dirDotOc * cosAngleSquare);
    double const quadC = std::pow(ocDotAxis, 2) - OcDotOC * cosAngleSquare;
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
    Ameth::Vec3D const tipToPoint = rec.point - center;
    double const cosAngleSquare = std::pow(std::cos(angle), 2);
    Ameth::Vec3D normal = axis * tipToPoint.dot(axis) - tipToPoint * cosAngleSquare;
    rec.normal = normal.normalized();
    if (ray.direction.dot(rec.normal) > 0)
        rec.normal = rec.normal * -1;
    rec.material = _material;
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
        return std::make_unique<RayTracer::Cone>(conePayload.position, conePayload.rotation, conePayload.angle, std::move(conePayload.material));
    };
    factory.add("cone", f);
}
