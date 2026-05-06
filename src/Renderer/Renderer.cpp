/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Renderer
*/

#include "Renderer/Renderer.hpp"
#include "Ray/Ray.hpp"
#include "Scene/Scene.hpp"

#include <cstddef>
#include <limits>
#include <iostream>

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
