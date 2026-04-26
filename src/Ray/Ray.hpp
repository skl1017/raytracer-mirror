/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Ray
*/

#pragma once

#include "Math/Ameth.hpp"
#include "plugins/IMaterial.hpp"

#include <memory>

class Ray {
public:
    struct HitRecord {
        double t{};
        Ameth::Vec3D point{};
        Ameth::Vec3D normal{};
        double u{};
        double v{};
        std::shared_ptr<IMaterial> material{};
    };

    Ameth::Vec3D origin{};
    Ameth::Vec3D direction{};

    Ameth::Vec3D at(double t) const { return origin + direction * t; }
};
