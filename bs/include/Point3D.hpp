/*
** EPITECH PROJECT, 2026
** Point3D
** File description:
** 
*/

#ifndef POINT3D
    #define POINT3D
    #include "Vector.hpp"

namespace Math {
    class Point3D
    {
    public:
        double x;
        double y;
        double z;

        Point3D(double x, double y = 0, double z = 0);
        Point3D() = default;
        ~Point3D() =default;

        Point3D operator+(Vector3D vec);
        void operator+=(Vector3D vec);
    };
};

#endif