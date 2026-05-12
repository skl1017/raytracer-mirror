/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Plane
*/

#include "Plane.hpp"

namespace RayTracer
{
    Plane::Plane(char axis, double position, std::shared_ptr<IMaterial> material):APrimitive(material),_axis(axis),_position(position){}

    extern "C"
    {
        void registerPlugin(PluginFactory &factory){
            PluginFactory::iPrimitiveCreateFunction f = [](const RayTracer::PluginFactory::primitivePayload &p)
            {
                auto planePayload = std::get<PluginFactory::plane_payload_t>(p);
                return std::make_unique<Plane>(planePayload.axis, planePayload.position, planePayload.material);
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
