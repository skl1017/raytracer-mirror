/*
** EPITECH PROJECT, 2026
** Point3D
** File description:
** 
*/

#include "Point3D.hpp"


Math::Point3D::Point3D(double x, double y, double z):
    x(x), y(y), z(z)
{
}

Math::Point3D Math::Point3D::operator+(Vector3D vec)
{
    return Math::Point3D(x + vec.x, y + vec.y, z + vec.z);
}

void Math::Point3D::operator+=(Vector3D vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
}
