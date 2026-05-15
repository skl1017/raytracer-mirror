/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Plane
*/

#include "Plane.hpp"
#include "Math/Ameth.hpp"
#include "plugins/APrimitive.hpp"
#include <cstdlib>
#include <optional>
#include <utility>

namespace RayTracer
{
    Plane::Plane(double position, Ameth::Vec3D rotation, std::shared_ptr<IMaterial> material) :
    APrimitive(material, rotation), _position(position)
    {};

std::optional<std::pair<double, double>> Plane::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    if (dir.length() < 1e-12)
        return std::nullopt;
    Ameth::Vec3D normal = _axis.normalized();
    double denom = dir.dot(normal);
    double t = 0;

    if (std::abs(denom) < 1e-6)
        return std::nullopt;
    t = (_point - origin).dot(normal) / denom;
    if (t < 0)
        return std::nullopt;
    return std::make_pair(t, 0);
}

void Plane::fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const
{
    rec.t = t;
    rec.point = ray.at(t);
    rec.normal = _axis.normalized();
    rec.material = _material;

    if (ray.direction.dot(rec.normal) > 0)
        rec.normal = rec.normal * -1;
}

}

extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
    RayTracer::PluginFactory::iPrimitiveCreateFunction const f
        = [](RayTracer::PluginFactory::primitivePayload const &p) -> std::unique_ptr<IPrimitive> {
        auto const planePayload = std::get<RayTracer::PluginFactory::plane_payload_t>(p);
        return std::make_unique<RayTracer::Plane>(planePayload.position, planePayload.rotation, std::move(planePayload.material));
    };
    factory.add("plane", f);
}

