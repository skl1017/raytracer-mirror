/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#include "Renderer/Renderer.hpp"

Ameth::Color Renderer::normalToColor(Ameth::Vec3D const &n) noexcept
{
    return Ameth::Color(0.5 * (n.x + 1.0), 0.5 * (n.y + 1.0), 0.5 * (n.z + 1.0));
}
