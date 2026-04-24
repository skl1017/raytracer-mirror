/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** APrimitive
*/

#pragma once

#include "plugins/IPrimitive.hpp"

#include <optional>
#include <utility>

class APrimitive : public IPrimitive {
public:
    bool hit(Camera::Ray const &ray, Camera::HitRecord &rec) const final
    {
        auto ts = lineTValues(ray.origin, ray.direction);
        if (!ts)
            return false;
        auto tHit = firstForwardHit(*ts);
        if (!tHit)
            return false;
        fillHitRecord(ray, *tHit, rec);
        return true;
    }

protected:
    std::optional<double> firstForwardHit(std::optional<std::pair<double, double>> ts) const noexcept
    {
        double const t0 = ts->first;
        double const t1 = ts->second;
        double tHit = -1.0;
        if (t0 > 0.0)
            tHit = t0;
        if (t1 > 0.0 && (tHit < 0.0 || t1 < tHit))
            tHit = t1;
        if (tHit <= 0.0)
            return std::nullopt;
        return tHit;
    }
    virtual std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const = 0;
    virtual void fillHitRecord(Camera::Ray const &ray, double t, Camera::HitRecord &rec) const = 0;
};
