/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#pragma once

#include "Math/Ameth.hpp"

class Renderer {
public:
    static Ameth::Color normalToColor(Ameth::Vec3D const &n) noexcept;
};
