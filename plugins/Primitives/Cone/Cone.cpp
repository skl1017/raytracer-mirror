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

Cone::Cone(Ameth::Vec3D c, Ameth::Vec3D rotation, double height, double baseRadius, std::shared_ptr<IMaterial> material)
    : APrimitive(material, rotation),
      center(c),
      angle(height > 0.0 ? std::atan2(std::max(0.0, baseRadius), height) : 0.0),
      _height(height),
      _baseRadius(std::max(0.0, baseRadius))
{
}

Ameth::Aabb Cone::boundingBox() const
{
    double const extent = _baseRadius + _height;
    Ameth::Vec3D const half(extent, extent, extent);
    return {center - half, center + half};
}

bool Cone::onForwardCone(double t, double ocDotAxis, double dirDotAxis) const
{
    if (t <= 0.0)
        return false;
    return ocDotAxis + t * dirDotAxis > 0.0;
}

double Cone::toRayT(double t, double invDirLen) const
{
    return t * invDirLen;
}

std::optional<std::pair<double, double>> Cone::handleNoise(double quadA, double quadB, double ocDotAxis, double dirDotAxis,
    double invDirLen) const
{
    if (std::abs(quadA) < 1e-12)
        return std::nullopt;
    double const t = -quadB / (2.0 * quadA);
    if (!onForwardCone(t, ocDotAxis, dirDotAxis))
        return std::nullopt;
    return std::make_pair(toRayT(t, invDirLen), -1.0);
}

std::optional<std::pair<double, double>> Cone::handleMirrorCone(double tMinusSqrt, double tPlusSqrt, double ocDotAxis,
    double dirDotAxis, double invDirLen) const
{
    bool const okMinus = onForwardCone(tMinusSqrt, ocDotAxis, dirDotAxis);
    bool const okPlus = onForwardCone(tPlusSqrt, ocDotAxis, dirDotAxis);
    if (!okMinus && !okPlus)
        return std::nullopt;
    if (okMinus && okPlus)
        return std::make_pair(toRayT(tMinusSqrt, invDirLen), toRayT(tPlusSqrt, invDirLen));
    double const t = okMinus ? tMinusSqrt : tPlusSqrt;
    return std::make_pair(toRayT(t, invDirLen), -1.0);
}

std::optional<std::pair<double, double>> Cone::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    double const dirLen = dir.length();
    if (dirLen < 1e-12)
        return std::nullopt;
    double const invDirLen = 1.0 / dirLen;

    Ameth::Vec3D const axis = _axis.normalized();
    Ameth::Vec3D const originToCenter = origin - center;
    double const dirDotAxis = dir.dot(axis) * invDirLen;
    double const ocDotAxis = originToCenter.dot(axis);
    double const dirDotOc = dir.dot(originToCenter) * invDirLen;
    double const OcDotOC = originToCenter.dot(originToCenter);
    double const cosAngleSquare = std::pow(std::cos(angle), 2);
    double const quadA = std::pow(dirDotAxis, 2) - cosAngleSquare;
    double const quadB = 2.0 * (dirDotAxis * ocDotAxis - dirDotOc * cosAngleSquare);
    double const quadC = std::pow(ocDotAxis, 2) - OcDotOC * cosAngleSquare;
    double const discriminant = std::pow(quadB, 2) - (4 * quadA * quadC);
    if (discriminant < 0.0)
        return std::nullopt;
    if (discriminant < 1e-12)
        return handleNoise(quadA, quadB, ocDotAxis, dirDotAxis, invDirLen);
    double const sqrtDisc = std::sqrt(discriminant);
    double const tMinusSqrt = (-quadB - sqrtDisc) / (2.0 * quadA);
    double const tPlusSqrt = (-quadB + sqrtDisc) / (2.0 * quadA);
    return handleMirrorCone(tMinusSqrt, tPlusSqrt, ocDotAxis, dirDotAxis, invDirLen);
}

void Cone::fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const
{
    rec.t = t;
    rec.point = ray.at(t);
    Ameth::Vec3D const axis = _axis.normalized();
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
        return std::make_unique<RayTracer::Cone>(
            conePayload.position,
            conePayload.rotation,
            conePayload.height,
            conePayload.radius,
            std::move(conePayload.material));
    };
    factory.add("cone", f);
}
