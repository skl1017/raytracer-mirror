# pragma once
#include <string>
#include "Math/Point3D.hpp"

#include "RayTracer/Ray.hpp"

enum PLUGIN {
    PRIMITIVE,
    MATERIAL,
    LIGHT
};

class IPrimitive {
    public:
        virtual std::string getName() const = 0;
        virtual Math::Point3D<double> pointAt(double u, double v) = 0;
        virtual bool hits(RayTracer::Ray) = 0;
        virtual ~IPrimitive() = default;
};

