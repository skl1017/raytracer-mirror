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
#include <utility>

namespace RayTracer {

Cylinder::Cylinder(Ameth::Vec3D c, double r, Ameth::Vec3D rotation, std::shared_ptr<IMaterial> material): APrimitive(material), center(c),
      radius(std::max(0.0, r)), rotation(rotation) {}

Ameth::Vec3D getProjection(Ameth::Vec3D vecteur, Ameth::Vec3D axis)
{
   return vecteur - axis * vecteur.dot(axis);
}

/*
a = (D - (D·V)V) · (D - (D·V)V)
b = 2 * ((D - (D·V)V) · (CO - (CO·V)V))
c = (CO - (CO·V)V) · (CO - (CO·V)V) - r²
*/

std::optional<std::pair<double, double>> Cylinder::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vec3D const originToCenter = origin - center;
    double const DirDotAxis = dir.dot(axis);
    double const OcDotAxis = originToCenter.dot(axis);
    Ameth::Vec3D const dirProjection = dir - axis * DirDotAxis;
    Ameth::Vec3D const ocProjection = originToCenter - axis * OcDotAxis;
    double const quadA = dirProjection.dot(dirProjection);
    double const quadB = 2 * dirProjection.dot(ocProjection);
    double const quadC = ocProjection.dot(ocProjection) - std::pow(radius, 2);
    if (std::abs(quadA) < 1e-12)
        return std::nullopt;
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
    Ameth::Vec3D const tipToPoint = rec.point - center;
    Ameth::Vec3D normal = tipToPoint - axis * tipToPoint.dot(axis);
    rec.normal = normal.normalized();
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
        return std::make_unique<RayTracer::Cylinder>(cylinderPayload.position, cylinderPayload.r, cylinderPayload.rotation, std::move(cylinderPayload.material));
    };
    factory.add("cylinder", f);
}
