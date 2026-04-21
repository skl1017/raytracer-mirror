/*
** EPITECH PROJECT, 2026
** ray
** File description:
** 
*/

#ifndef RAY
    #define RAY
    #include "Point3D.hpp"
    #include "Vector.hpp"

namespace RayTracer
{
    class Ray
    {
    private:
        Math::Point3D _origin;
        Math::Vector3D _direction;
    public:
        Ray() = default;
        Ray(Math::Point3D origin, Math::Vector3D direction) : _origin(_origin), _direction(direction){};
        ~Ray() = default;

        Math::Point3D &getOrigin() {return _origin;};
        Math::Vector3D &getDirection() {return _direction;};
    };
}


#endif