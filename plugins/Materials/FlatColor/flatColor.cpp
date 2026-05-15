/*
** EPITECH PROJECT, 2026
** RayTracer-mirror
** File description:
** RayTracer::flatColor
*/

#include "flatColor.hpp"
#include <iostream>
#include "PluginFactory/PluginFactory.hpp"

RayTracer::flatColor::flatColor(Ameth::Color color, int transparency, double refraction, double reflection):
    AMaterial(transparency, refraction, reflection),
    _surfaceColor(color)
{
}

RayTracer::flatColor::~flatColor()
{
}

Ameth::Color RayTracer::flatColor::getColor(Ameth::Color IncomingLightColor)
{
    Ameth::Color finalColor;

    finalColor.r = _surfaceColor.r * IncomingLightColor.r;
    finalColor.g = _surfaceColor.g * IncomingLightColor.g;
    finalColor.b = _surfaceColor.b * IncomingLightColor.b;

    return finalColor;
}

extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
    RayTracer::PluginFactory::iMaterialCreateFunction const f
        = [](RayTracer::PluginFactory::materialPayload const &p) -> std::shared_ptr<IMaterial> {
        auto const materialPayload = std::get<RayTracer::PluginFactory::flatColor_payload_t>(p);
        return std::make_shared<RayTracer::flatColor>(materialPayload.color,
            materialPayload.transparency, materialPayload.refraction, materialPayload.reflection);
    };
    factory.add("flatColor", f);
}
