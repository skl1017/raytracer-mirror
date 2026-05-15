/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** IMaterial
*/

#pragma once
#include "Math/Ameth.hpp"
class IMaterial {
public:
    virtual Ameth::Color getColor(Ameth::Color IncomingLightColor) = 0;
    virtual bool isTransparent() = 0;
    virtual double getTransparency() = 0;
    virtual double getRefraction() = 0;
    virtual bool isReflecting() = 0;
    virtual double getReflection() = 0;
    virtual ~IMaterial() = default;
};
