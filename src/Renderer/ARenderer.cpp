/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ARendere
*/

#include "ARenderer.hpp"

void ARenderer::renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler)
{
    unsigned const width = camera->imageWidth();
    unsigned const height = camera->imageHeight();
    std::vector<Ameth::Color> &hdr = camera->getHDRImage();
    auto const &primitives = scene._primitives;

    scheduler.clear();
    scheduler.submit(0, static_cast<int>(width * height), 32, [&](int idx)
    {
        unsigned px = static_cast<unsigned>(idx) % width;
        unsigned py = static_cast<unsigned>(idx) / width;
        double const u = (static_cast<double>(px) + 0.5) / static_cast<double>(width);
        double const v = (static_cast<double>(py) + 0.5) / static_cast<double>(height);
        Ray const ray = camera->ray(u, v);
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
            hdr[idx] = computeLight(closestRec, scene);
        else
            hdr[idx] = _bg;
    });
    scheduler.run();
}