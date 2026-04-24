/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Plane
*/

#pragma once
#include "plugins/IPrimitive.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include "Math/Ameth.hpp"
namespace RayTracer
{
    class Plane : public IPrimitive
    {
        public:
            Plane(char, double, const Ameth::Color &);

            std::string getName() const{};
            Ameth::Vec3D pointAt(double u, double v){};
            bool hits(Camera::Ray const &ray){};



        private:
            char _axis;
            double _position;
            Ameth::Color _color;


    };
}
