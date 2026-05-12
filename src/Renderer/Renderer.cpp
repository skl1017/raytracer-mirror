/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#include "Renderer/Renderer.hpp"
#include "Scene/Scene.hpp"

#include <cstddef>
#include <limits>
#include <iostream>
#include <algorithm>

Ameth::Color Renderer::normalToColor(Ameth::Vec3D const &n) noexcept
{
    return Ameth::Color(0.5 * (n.x + 1.0), 0.5 * (n.y + 1.0), 0.5 * (n.z + 1.0));
}

void Renderer::renderNormals(RayTracer::Scene &scene, ParallelImageScheduler &scheduler)
{
    std::unique_ptr<Camera> &cam = scene._cameras[0];
    unsigned const width = cam->imageWidth();
    unsigned const height = cam->imageHeight();
    std::vector<Ameth::Color> &hdr = cam->getHDRImage();
    auto const &primitives = scene._primitives;

    scheduler.clear();
    scheduler.submit(0, static_cast<int>(width * height), 32, [&](int idx)
    {
        unsigned px = static_cast<unsigned>(idx) % width;
        unsigned py = static_cast<unsigned>(idx) / height;
        Ray const ray = cam->ray(px, py);
        double closestT = std::numeric_limits<double>::infinity();
        bool hitAny = false;
        Ray::HitRecord closestRec{};

        for (auto const &prim : primitives) {
            Ray::HitRecord rec{};
            if (prim->hit(ray, rec) && rec.t < closestT) {
                hitAny = true;
                closestT = rec.t;
                closestRec = rec;
            }
        }
        if (hitAny)
            hdr[idx] = normalToColor(closestRec.normal);
        else
            hdr[idx] = Ameth::Color(0.0, 0.0, 0.2);
    });
    scheduler.run();
}

Ameth::Color Renderer::computeLight(Ray::HitRecord &hit, RayTracer::Scene &scene)
{
    Ameth::Color lightColor(0, 0, 0);
    Ameth::Color finalColor(0, 0, 0);

    for (size_t i = 0; i < scene._lights.size(); i++) {
        lightColor = scene._lights[i]->getIllumination(hit);

        finalColor.r = std::max(finalColor.r, lightColor.r);
        finalColor.g = std::max(finalColor.g, lightColor.g);
        finalColor.b = std::max(finalColor.b, lightColor.b);
    }
    return finalColor;
}
