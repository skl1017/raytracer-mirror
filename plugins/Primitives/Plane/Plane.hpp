/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Plane
*/

#pragma once
#include "plugins/APrimitive.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include "Math/Ameth.hpp"
#include "Camera/Camera.hpp"
#include <optional>
#include <string>

namespace RayTracer
{

class Plane : public APrimitive {
public:
    Plane(double position, Ameth::Vec3D rotation, std::shared_ptr<IMaterial> material = nullptr);
    std::string getName() const override { return "Plane"; }
    Ameth::Vec3D getNormal() const;
    Ameth::Vec3D pointAt(double u, double v) const override {(void)u; (void)v; return {};};

    double _position;
    Ameth::Vec3D _point;

protected:
    std::string name{"Plane"};
    void fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const override;
    std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const override;
};

}
