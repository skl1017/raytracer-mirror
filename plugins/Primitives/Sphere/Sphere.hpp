# pragma once

#include "plugins/IPrimitive.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include <cmath>
#include <string>

namespace RayTracer {
    class Sphere : IPrimitive {
        public:
            Sphere(Math::Point3D<double> c, double r) : center(c), radius(r) {}
            bool hits(RayTracer::Ray<double> ray) override
            {
                Math::Vector3D<double> vector(
                    center.x - ray.origin.x,
                    center.y - ray.origin.y,
                    center.z - ray.origin.z
                );
                double length = std::sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
                double distance = length - radius;
                return (distance <= 0) ? (true) : false ;
            }
            std::string getName() const override { return name; }
            Math::Point3D<double> pointAt(double u, double v)
            {
                return center;
            }
            Math::Point3D<double> center;
            double radius;
        private:
            std::string name;
    };
}
