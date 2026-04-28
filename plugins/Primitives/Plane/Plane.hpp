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
namespace RayTracer
{
    class Plane : public APrimitive
    {
        public:
            Plane(char, double, const Ameth::Color &);

            std::string getName() const{};
            Ameth::Vec3D pointAt(double u, double v) const override{}

        protected:
            void fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const override{}
            std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const{}



        private:
            char _axis;
            double _position;
            Ameth::Color _color;


    };
}
