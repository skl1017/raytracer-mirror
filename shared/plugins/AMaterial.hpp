/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AMaterial
*/

#pragma once
#include <cstddef>
#include "plugins/IMaterial.hpp"

namespace RayTracer
{

class AMaterial : public IMaterial
{
protected:
    std::size_t _transparency;
    double _refraction;
    double _reflection;
public:
    AMaterial(std::size_t transparency, double refraction, double reflection) : 
        _transparency(transparency),
        _refraction(refraction),
        _reflection(reflection) 
    {};
    ~AMaterial() {};

    bool isTransparent() override {
        return _transparency != 0;
    };

    double getTransparency() override {
        return 1.0 - _transparency / 100;
    };

    double getRefraction() override {
        return _refraction;
    };

    bool isReflecting() override {
        return _reflection != 0;
    };

    double getReflection() override {
        return _reflection;
    }
;
};
}