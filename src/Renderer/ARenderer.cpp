/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ARendere
*/

#include "ARenderer.hpp"

bool ARenderer::isRayHitting(RayTracer::Scene &scene, Ray const &raycast,
    Ray::HitRecord &rec, std::size_t depth)
{
    if (depth <= 0)
        return false;
    if (scene._bvh.empty())
        return false;
    rec.t = std::numeric_limits<double>::infinity();
    return scene._bvh.hit(raycast, rec);
}

bool ARenderer::isRayHitting(RayTracer::Scene &scene, Ray const &raycast, Ray::HitRecord &rec)
{
    if (scene._bvh.empty())
        return false;
    rec.t = std::numeric_limits<double>::infinity();
    return scene._bvh.hit(raycast, rec);
}

void ARenderer::renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera, ParallelImageScheduler &scheduler)
{
    unsigned const width = camera->imageWidth();
    unsigned const height = camera->imageHeight();
    std::vector<Ameth::Color> &hdr = camera->getHDRImage();

    scheduler.clear();
    scheduler.submit(0, static_cast<int>(width * height), 32, [&](int idx)
    {
        unsigned px = static_cast<unsigned>(idx) % width;
        unsigned py = static_cast<unsigned>(idx) / width;
        double const u = (static_cast<double>(px) + 0.5) / static_cast<double>(width);
        double const v = (static_cast<double>(py) + 0.5) / static_cast<double>(height);
        Ray const ray = camera->ray(u, v);
        Ray::HitRecord closestRec{};

        if (isRayHitting(scene, ray, closestRec))
            hdr[idx] = computeLight(closestRec, ray,scene);
        else
            hdr[idx] = _bg;
    });
    scheduler.run();
}