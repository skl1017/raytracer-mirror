/*
** EPITECH PROJECT, 2026
** Sphere
** File description:
** 
*/

#ifndef SPHERE
    #define SPHERE
    #include "Point3D.hpp"
    #include "Ray.hpp"
    #include "Math.hpp"

namespace RayTracer
{
    class Sphere
    {
    private:
        Math::Point3D _origin;
        double _radius;
    public:
        Sphere(Math::Point3D origin, double radius) : _origin(origin), _radius(radius){};
        ~Sphere() = default;

bool hits(RayTracer::Ray &raycast) {
    Math::Vector3D dir = raycast.getDirection();
    Math::Point3D o = raycast.getOrigin();

    Math::Vector3D oc(o.x - _origin.x,
                      o.y - _origin.y,
                      o.z - _origin.z);

    double a = dir.dot(dir);
    double b = 2.0 * oc.dot(dir);
    double c = oc.dot(oc) - _radius * _radius;

    return (b * b - 4 * a * c) > 0;
}

};
}


#endif