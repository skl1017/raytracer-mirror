/*
** EPITECH PROJECT, 2026
** Vector
** File description:
** 
*/

#include "Vector.hpp"
#include <cmath>

Math::Vector3D::Vector3D(double x, double y, double z):
    x(x), y(y), z(z)
{
}

double Math::Vector3D::length()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

double Math::Vector3D::dot(Vector3D oth)
{
    return x * oth.x + y * oth.y + z * oth.z;
}

Math::Vector3D Math::Vector3D::normalize()
{
    double len = length();

    if (len == 0) {
        throw Math::DivideByZero();
    }
    return Math::Vector3D(x / len, y / len, z / len);
}

Math::Vector3D Math::Vector3D::operator+(Vector3D oth)
{
    return Math::Vector3D(x + oth.x, y + oth.y, z + oth.z);
}

void Math::Vector3D::operator+=(Vector3D oth)
{
    x += oth.x;
    y += oth.y;
    z += oth.z;
}

Math::Vector3D Math::Vector3D::operator-(Vector3D oth)
{
    return Math::Vector3D(x - oth.x, y - oth.y, z - oth.z);
}

void Math::Vector3D::operator-=(Vector3D oth)
{
    x -= oth.x;
    y -= oth.y;
    z -= oth.z;
}

Math::Vector3D Math::Vector3D::operator*(double mult)
{
    return Math::Vector3D(x * mult, y * mult, z * mult);
}

void Math::Vector3D::operator*=(double mult)
{
    x *= mult;
    y *= mult;
    z *= mult;
}


Math::Vector3D Math::Vector3D::operator*(Vector3D oth)
{
    return Math::Vector3D(
        y * oth.z - z * oth.y,
        z * oth.x - x * oth.z,
        x * oth.y - y * oth.x);
}

void Math::Vector3D::operator*=(Vector3D oth)
{
    x = y * oth.z - z * oth.y;
    y = z * oth.x - x * oth.z;
    z = x * oth.y - y * oth.x;
}

Math::Vector3D Math::Vector3D::operator/(double div)
{
    if (div == 0){
        throw Math::DivideByZero();
    }
    return Math::Vector3D(x / div, y / div, z / div);
}

void Math::Vector3D::operator/=(double div)
{
    if (div == 0){
        throw Math::DivideByZero();
    }
    x /= div;
    y /= div;
    z /= div;
}
