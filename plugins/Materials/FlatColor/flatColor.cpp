/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** flatColor
*/

#include "flatColor.hpp"
#include <iostream>

flatColor::flatColor(Ameth::Color color, int transparency):
    _surfaceColor(color),
    _transparency(transparency)
{
}

flatColor::~flatColor()
{
}

Ameth::Color flatColor::getColor(Ameth::Color IncomingLightColor)
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

bool flatColor::isTransparent()
{
    return _transparency != 0;
}


double flatColor::getTransparency()
{
    return 1.0 - _transparency / 100;
}
