/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** flatColor
*/

#pragma once
#include "plugins/IMaterial.hpp"

class flatColor : public IMaterial
{
public:
    flatColor(Ameth::Color color, int transparency);
    ~flatColor() override;

    Ameth::Color getColor(Ameth::Color IncomingLightColor) override;
    bool isTransparent() override;
    double getTransparency() override;
private:
    double _transparency;
    Ameth::Color _surfaceColor;
};
