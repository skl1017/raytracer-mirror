/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Sphere
*/

#pragma once

#include "Math/Ameth.hpp"
#include "plugins/IMaterial.hpp"
#include "plugins/APrimitive.hpp"

#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace RayTracer {

class Sphere : public APrimitive {
public:
    Sphere(Ameth::Vec3D c, double r, std::shared_ptr<IMaterial> material = nullptr);

    std::string getName() const override;
    Ameth::Vec3D pointAt(double u, double v) const override;

    Ameth::Vec3D center;
    double radius{};

protected:
    void fillHitRecord(Camera::Ray const &ray, double t, Camera::HitRecord &rec) const override;
    std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const;

    std::shared_ptr<IMaterial> _material;
    std::string name{"Sphere"};
};

} // namespace RayTracer
