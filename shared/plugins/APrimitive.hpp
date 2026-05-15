/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** APrimitive
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Transformation/TransformationFactory.hpp"
#include "plugins/IPrimitive.hpp"

#include <optional>
#include <utility>

class APrimitive : public IPrimitive {
public:
    APrimitive(std::shared_ptr<IMaterial> material, Ameth::Vec3D rotation): _material(std::move(material))
    {
        Ameth::Matrix<double, 4, 1> axisMatrix = {{
            {{_axis.x}, 
            {_axis.y}, 
            {_axis.z}, 
            {0}}
        }};
        Ameth::Matrix<double, 4, 4> rotationMatrix =
        TransformationFactory::getXRotation(rotation.x) *
        TransformationFactory::getYRotation(rotation.y) *
        TransformationFactory::getZRotation(rotation.z);
        axisMatrix = rotationMatrix * axisMatrix;
        _axis = {axisMatrix[0][0], axisMatrix[1][0], axisMatrix[2][0]};
    }

    bool hit(Ray const &ray, Ray::HitRecord &rec) const final
    {
        auto ts = lineTValues(ray.origin, ray.direction);
        if (!ts)
            return false;
        auto tHit = firstForwardHit(ts);
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
    Ameth::Vec3D _axis = {0, 1, 0};
    virtual std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const = 0;
    virtual void fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const = 0;
    std::shared_ptr<IMaterial> _material;
};
