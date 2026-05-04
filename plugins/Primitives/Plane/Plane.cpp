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

    extern "C"
    {
        void registerPlugin(PluginFactory &factory){
            PluginFactory::iPrimitiveCreateFunction f = [](const RayTracer::PluginFactory::primitivePayload &p)
            {
                auto planePayload = std::get<PluginFactory::plane_payload_t>(p);
                return std::make_unique<Plane>(planePayload.axis, planePayload.position, planePayload.color);
            };
            factory.add("plane", f);
            return;
        }

        PLUGIN getLibType()
        {
            return PRIMITIVE;
        }
    }
}
