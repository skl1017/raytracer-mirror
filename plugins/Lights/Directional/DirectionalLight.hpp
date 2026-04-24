/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DirectionalLight
*/

#pragma once
#include "plugins/ILight.hpp"

class DirectionalLight : public ILight
{
public:
    DirectionalLight(/* args */);
    ~DirectionalLight();
};
