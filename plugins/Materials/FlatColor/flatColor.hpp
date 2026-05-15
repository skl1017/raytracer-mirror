/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** flatColor
*/

#pragma once
#include "plugins/AMaterial.hpp"

namespace RayTracer
{
    class flatColor : public AMaterial
    {
public:
    flatColor(Ameth::Color color, int transparency = 0, double refraction = 0, double reflection = 0);
    ~flatColor() override;
    
    Ameth::Color getColor(Ameth::Color IncomingLightColor) override;
private:
    Ameth::Color _surfaceColor;
};

} 