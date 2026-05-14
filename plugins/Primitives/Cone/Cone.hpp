/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Cone
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

class Cone : public APrimitive {
public:
    Cone(Ameth::Vec3D c, Ameth::Vec3D rotation, double height, double baseRadius, std::shared_ptr<IMaterial> material = nullptr);
    std::string getName() const override;
    Ameth::Vec3D pointAt(double u, double v) const override;

    Ameth::Vec3D center;
    double angle;

protected:
    void fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const override;
    std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const override;
    std::string name{"Cone"};
};

} // namespace RayTracer
