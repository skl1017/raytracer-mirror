/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer
{
    Scene::Scene(std::vector<std::unique_ptr<IPrimitive>> primitives):
        _camera(Camera(Ameth::Vec3D(0.0, 200, -350), Ameth::Quaternion::identity(), 2.0 * std::atan(0.5), 1920, 1080)),
        _primitives(std::move(primitives))
    {
        
    }

    bool Scene::rayHitPrimitive(Camera::Ray &ray)
    {
        for (auto &&primitive : _primitives) {
            if (primitive->hits(ray)) {
                _hitColor = Ameth::Color(1.0, 0.0, 0.0);
                return true;
            }
        }
        return false;
    }

    std::vector<Ameth::Color> Scene::getScreen()
    {
        constexpr unsigned WIDTH = 1920;
        constexpr unsigned HEIGHT = 1080;
    
        for (unsigned x = 0; x < WIDTH; ++x) {
            for (unsigned y = 0; y < HEIGHT; ++y) {
                double u = (static_cast<double>(x) + 0.5) / static_cast<double>(WIDTH);
                double v = (static_cast<double>(y) + 0.5) / static_cast<double>(HEIGHT);
                Camera::Ray r = _camera.ray(u, v);
                std::size_t i = y * WIDTH + x;
                if (rayHitPrimitive(r)) {
                    _camera.getHDRImage()[i] = _hitColor;
                } else {
                    _camera.getHDRImage()[i] = Ameth::Color(0.0, 0.0, 1.0);
                }
            }
        }
        return _camera.getHDRImage();
    }
}
