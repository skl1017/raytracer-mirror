/*
** EPITECH PROJECT, 2026
** RayTracer-mirror
** File description:
** RayTracer::flatColor
*/

#include "flatColor.hpp"
#include <iostream>
#include "PluginFactory/PluginFactory.hpp"

RayTracer::flatColor::flatColor(Ameth::Color color, int transparency):
    _surfaceColor(color),
    _transparency(transparency)
{
}

RayTracer::flatColor::~flatColor()
{
}

Ameth::Color RayTracer::flatColor::getColor(Ameth::Color IncomingLightColor)
{
    Ameth::Color finalColor;

    finalColor.r = std::min(_surfaceColor.r, IncomingLightColor.r);
    finalColor.g = std::min(_surfaceColor.g, IncomingLightColor.g);
    finalColor.b = std::min(_surfaceColor.b, IncomingLightColor.b);

    if (_transparency == 0) {
        return finalColor;
    }
    return finalColor * (1.0 - (_transparency / 100));
}

bool RayTracer::flatColor::isTransparent()
{
    return _transparency != 0;
}


double RayTracer::flatColor::getTransparency()
{
    return 1.0 - _transparency / 100;
}

extern "C" void registerPlugin(RayTracer::PluginFactory &factory)
{
    RayTracer::PluginFactory::iMaterialCreateFunction const f
        = [](RayTracer::PluginFactory::materialPayload const &p) -> std::shared_ptr<IMaterial> {
        auto const materialPayload = std::get<RayTracer::PluginFactory::flatColor_payload_t>(p);
        return std::make_shared<RayTracer::flatColor>(materialPayload.color, materialPayload.transparency);
    };
    factory.add("flatColor", f);
}
