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

void Renderer::renderNormals(RayTracer::Scene &scene)
{

    std::unique_ptr<Camera> &cam = scene._cameras[0];
    unsigned const width = cam->imageWidth();
    unsigned const height = cam->imageHeight();
    std::vector<Ameth::Color> &hdr = cam->getHDRImage();
    auto const &primitives = scene._primitives;

    double const inf = std::numeric_limits<double>::infinity();

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            double const su = (static_cast<double>(x) + 0.5) / static_cast<double>(width);
            double const sv = (static_cast<double>(y) + 0.5) / static_cast<double>(height);
            Ray const ray = cam->ray(su, sv);
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
            if (hitAny)
                hdr[i] = computeLight(closestRec, scene);
            else
                hdr[i] = Ameth::Color(0.0, 0.0, 0.2);
        }
    }
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
