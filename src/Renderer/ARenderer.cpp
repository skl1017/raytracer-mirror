/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ARendere
*/

#include "ARenderer.hpp"

void ARenderer::renderScreen(RayTracer::Scene &scene, std::unique_ptr<Camera> &camera)
{
    unsigned const width = camera->imageWidth();
    unsigned const height = camera->imageHeight();
    std::vector<Ameth::Color> &hdr = camera->getHDRImage();
    auto const &primitives = scene._primitives;

    double const inf = std::numeric_limits<double>::infinity();

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            double const su = (static_cast<double>(x) + 0.5) / static_cast<double>(width);
            double const sv = (static_cast<double>(y) + 0.5) / static_cast<double>(height);
            Ray const ray = camera->ray(su, sv);
            std::size_t const i = y * width + x;

            bool hitAny = false;
            double closestT = inf;
            Ray::HitRecord closestRec{};

            for (auto const &prim : primitives) {
                Ray::HitRecord rec{};
                if (prim->hit(ray, rec) && rec.t < closestT) {
                    hitAny = true;
                    closestT = rec.t;
                    closestRec = rec;
                }
            }
            if (hitAny){
                hdr[i] = computeLight(closestRec, scene);
            } else
                hdr[i] = _bg;
        }
    }
}
