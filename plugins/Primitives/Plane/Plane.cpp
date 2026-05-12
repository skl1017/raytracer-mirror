/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Plane
*/

#include "Plane.hpp"

namespace RayTracer
{
    Plane::Plane(char axis, double position, const Ameth::Color& color):_axis(axis),_position(position),_color(color){}
}

extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
    RayTracer::PluginFactory::iPrimitiveCreateFunction const f
        = [](RayTracer::PluginFactory::primitivePayload const &p) -> std::unique_ptr<IPrimitive> {
        auto const planePayload = std::get<RayTracer::PluginFactory::plane_payload_t>(p);
        return std::make_unique<RayTracer::Plane>(planePayload.axis, planePayload.position, planePayload.color);
    };
    factory.add("plane", f);
}

