/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Renderer/ParallelImageScheduler.hpp"
#include "Ray/Ray.hpp"
#include "Scene/Scene.hpp"

class Renderer {
public:
    static Ameth::Color normalToColor(Ameth::Vec3D const &n) noexcept;
    static void renderNormals(RayTracer::Scene &scene, ParallelImageScheduler& scheduler);
private:
    static Ameth::Color computeLight(Ray::HitRecord &hit, RayTracer::Scene &scene);
};
