/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "plugins/IPrimitive.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include <iostream>
namespace RayTracer
{
    extern "C"
    {
        void registerPlugin(PluginFactory &factory){
            std::cout << "im called" << std::endl;
            PluginFactory::primtiveCreateFunction f = [](const RayTracer::PluginFactory::primitivePayload &p)
            {
                auto spherePayload = std::get<PluginFactory::sphere_payload_t>(p);
                return std::make_unique<Sphere>(spherePayload.position, spherePayload.r);
            };
            factory.add("sphere", f);
            return;
        }

        PLUGIN getLibType()
        {
            return PRIMITIVE;
        }
    }
}


