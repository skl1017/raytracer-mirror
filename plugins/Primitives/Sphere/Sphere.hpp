# pragma once

#include "plugins/IPrimitive.hpp"
#include "RayTracer/Ray.hpp"
#include "Math/Vector3D.hpp"
#include "Math/Point3D.hpp"
#include <cmath>
#include <string>

namespace RayTracer {
    class Sphere : public IPrimitive {
        public:
            Sphere() : radius(0) {}
            Sphere(Math::Point3D<double> c, double r) : center(c), radius(r) {}
            bool hits(RayTracer::Ray ray) override
            {
                Math::Vector3D<double> vector(
                    center.x - ray.getOrigin().x,
                    center.y - ray.getOrigin().y,
                    center.z - ray.getOrigin().z
                );
                double length = std::sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
                double distance = length - radius;
                return (distance <= 0) ? (true) : false ;
            }
            std::string getName() const override { return name; }
            Math::Point3D<double> pointAt(double u, double v) override
            {
                return center;
            }
            Math::Point3D<double> center;
            double radius;
            ~Sphere() {}
        private:
            std::string name = "Sphere";
    };
}
