/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include <iostream>
#include <memory>

Ameth::Color RayTracer::PointLight::getIllumination(Ray::HitRecord &hitRecord)
{
    Ameth::Color illumination = _LightColor;
    Ameth::Vec3D incidentLight = (_position - hitRecord.point).normalized();

    double ambient = 0.1;
    double angle = hitRecord.normal.dot(incidentLight);
    double intensity = ambient + std::max(0.0, angle);
    
    illumination *= intensity;
    return illumination;
}

extern "C" {
    void registerPlugin(RayTracer::PluginFactory &factory)
    {
        RayTracer::PluginFactory::iLightCreateFunction const f = 
            [](RayTracer::PluginFactory::lightPayload const &p) -> std::unique_ptr<ILight> {
                auto const payload = std::get<RayTracer::PluginFactory::pointlight_payload_t>(p);
                return std::make_unique<RayTracer::PointLight>(payload.pos, payload.color);
            };

        factory.add("pointLight", f);
    }

    ILight *create()
    {
        return new RayTracer::PointLight(Ameth::Vec3D(0, 0, 0), Ameth::Color(0, 0, 0));
    }

    PLUGIN getLibType()
    {
        return LIGHT;
    }

}