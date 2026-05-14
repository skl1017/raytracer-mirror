/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Cylinder
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

class Cylinder : public APrimitive {
public:
    Cylinder(Ameth::Vec3D c, double r, Ameth::Vec3D axis, std::shared_ptr<IMaterial> material = nullptr);
    std::string getName() const override;
    Ameth::Vec3D pointAt(double u, double v) const override;

    Ameth::Vec3D center;
    Ameth::Vec3D rotation;
    double radius{};

protected:
    void fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const override;
    std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const override;
    Ameth::Vec3D _axis;
    std::string name{"Cylinder"};
};

} // namespace RayTracer
