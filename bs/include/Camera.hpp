/*
** EPITECH PROJECT, 2026
** Camera
** File description:
** 
*/

#ifndef CAM
    #define CAM
    #include "Point3D.hpp"
    #include "Rectangle.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    class Camera
    {
    private:
        Math::Point3D _origin;
        Rectangle _screen;
    public:
        Camera(Math::Vector3D length, Math::Vector3D width):
            _origin(Math::Point3D(0, 0, 10)),
            _screen(Rectangle(Math::Point3D(-500, -500, 0), length, width)) {};
        ~Camera() = default;

        RayTracer::Ray ray(double u, double v) {
            Math::Point3D point = _screen.pointAt(u, v);
            Math::Vector3D dir(point.x - _origin.x, point.y - _origin.y, point.z - _origin.z);

            return RayTracer::Ray(_origin, dir);
        };
    };
}

#endif