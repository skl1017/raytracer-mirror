#pragma once

#include <cmath>

namespace Ameth {

class Vector3D {
public:
    double x;
    double y;
    double z;

    Vector3D()
        : x(0.0),
          y(0.0),
          z(0.0)
    {
    }

    Vector3D(double x, double y, double z)
        : x(x),
          y(y),
          z(z)
    {
    }

    double length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    double dot(Vector3D const &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3D operator+(Vector3D const &v) const
    {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vector3D &operator+=(Vector3D const &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3D operator+(double s) const
    {
        return {x + s, y + s, z + s};
    }

    Vector3D operator-(Vector3D const &v) const
    {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vector3D &operator-=(Vector3D const &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3D operator*(Vector3D const &v) const
    {
        return {x * v.x, y * v.y, z * v.z};
    }

    Vector3D &operator*=(Vector3D const &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector3D operator*(double s) const
    {
        return {x * s, y * s, z * s};
    }

    Vector3D &operator*=(double s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    Vector3D operator/(double s) const
    {
        return {x / s, y / s, z / s};
    }

    Vector3D &operator/=(double s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    Vector3D &operator/=(Vector3D const &v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vector3D pow(double e) const
    {
        return {std::pow(x, e), std::pow(y, e), std::pow(z, e)};
    }
};

inline Vector3D operator*(double s, Vector3D const &v)
{
    return v * s;
}

} // namespace Ameth
