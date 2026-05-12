/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Plane
*/

#include "Plane.hpp"
#include "plugins/APrimitive.hpp"
#include <optional>

namespace RayTracer
{
    Plane::Plane(char axis, double position, std::shared_ptr<IMaterial> material) :
    APrimitive(material), _axis(axis), _position(position) {};

void Plane::fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const
{

}

std::optional<std::pair<double, double>> Plane::lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const
{
    return std::nullopt;
}

}

extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
    RayTracer::PluginFactory::iPrimitiveCreateFunction const f
        = [](RayTracer::PluginFactory::primitivePayload const &p) -> std::unique_ptr<IPrimitive> {
        auto const planePayload = std::get<RayTracer::PluginFactory::plane_payload_t>(p);
        return std::make_unique<RayTracer::Plane>(planePayload.axis, planePayload.position, std::move(planePayload.material));
    };
    factory.add("plane", f);
}

