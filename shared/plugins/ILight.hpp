/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ILight
*/

#pragma once

#include "Ameth.hpp"
#include "Camera/Camera.hpp"

class ILight
{
public:
    virtual Ameth::Color getIllumination() = 0;
};
