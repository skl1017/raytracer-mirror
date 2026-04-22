/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DLLoader
*/

#pragma once


//#include "Math/Ameth.hpp"
//#include "plugins/IPrimitive.hpp"
//
//namespace RayTracer {
//    class Rectangle3D : public IPrimitive {
//        public:
//            Rectangle3D() : origin(0, 0, 0), bottom_side(1, 0, 0), left_side(0, 1, 0) {};
//            Math::Point3D<double> pointAt(double u, double v) override
//            {
//                return Math::Point3D<double>(u, v, 0);
//            };
//            Math::Point3D<double> origin;
//            Ameth::Vector3D bottom_side;
//            Ameth::Vector3D left_side;
//            bool hits(RayTracer::Ray ray) override
//            {
//                return true;
//            }
//            std::string getName() const override { return name; }
//            ~Rectangle3D() {}
//        private:
//            std::string name = "Rectangle";
//    };
//}