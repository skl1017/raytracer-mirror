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
    class Plane : public APrimitive
    {
        public:
            Plane(char, double, const Ameth::Color &);

            std::string getName() const override { return "Plane"; }
            Ameth::Vec3D pointAt(double u, double v) const override
            {
                (void)u;
                (void)v;
                return {0.0, 0.0, 0.0};
            }

        protected:
            void fillHitRecord(Ray const &ray, double t, Ray::HitRecord &rec) const override
            {
                (void)ray;
                (void)t;
                (void)rec;
            }
            std::optional<std::pair<double, double>> lineTValues(Ameth::Vec3D const &origin, Ameth::Vec3D const &dir) const override
            {
                (void)origin;
                (void)dir;
                return std::nullopt;
            }



        private:
            char _axis;
            double _position;
            Ameth::Color _color;


    };
}
