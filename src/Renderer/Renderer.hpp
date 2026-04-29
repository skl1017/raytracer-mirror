/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#pragma once

#include "Math/Ameth.hpp"

namespace RayTracer {
    class Scene;
}

class Renderer {
public:
    static Ameth::Color normalToColor(Ameth::Vec3D const &n) noexcept;
    /** Writes shaded samples into `scene.camera().getHDRImage()` (normal visualization). */
    static void renderNormals(RayTracer::Scene &scene);
};
