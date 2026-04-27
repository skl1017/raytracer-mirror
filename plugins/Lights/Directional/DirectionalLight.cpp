/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include "PluginFactory/PluginFactory.hpp"

Ameth::Color RayTracer::DirectionalLight::getIllumination(Ray::HitRecord &hitRecord)
{
    Ameth::Color illumination = _LightColor;
    Ameth::Vec3D incidentLight = Ameth::Vec3D(0, 0, 0) - _direction;
    double ambient = 0.1;
    double angle = hitRecord.normal.dot(incidentLight.normalized());
    double intensity = ambient + std::max(0.0, angle);

    return illumination * intensity;
}

extern "C" {
    void registerPlugin(RayTracer::PluginFactory &factory)
    {
        RayTracer::PluginFactory::iLightCreateFunction const f = 
            [](RayTracer::PluginFactory::lightPayload const &p) -> std::unique_ptr<ILight> {
                auto const payload = std::get<RayTracer::PluginFactory::directionlight_payload_t>(p);
                return std::make_unique<RayTracer::DirectionalLight>(payload.direction, payload.color);
            };

        factory.add("pointLight", f);
    }

    ILight *create()
    {
        return new RayTracer::DirectionalLight(Ameth::Vec3D(0, 0, 0), Ameth::Color(0, 0, 0));
    }

    PLUGIN getLibType()
    {
        return LIGHT;
    }

}