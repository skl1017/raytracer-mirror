#pragma once

#include <cmath>

namespace Ameth {

class Vec3D {
public:
    double x;
    double y;
    double z;

    Vec3D() : x(0.0), y(0.0), z(0.0) {}
    Vec3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    double dot(Vec3D const &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3D operator+(Vec3D const &v) const
    {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3D operator+(double s) const
    {
        return {x + s, y + s, z + s};
    }

    Vec3D &operator+=(Vec3D const &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3D &operator+=(double s)
    {
        x += s;
        y += s;
        z += s;
        return *this;
    }

    Vec3D operator-(Vec3D const &v) const
    {
        return {x - v.x, y - v.y, z - v.z};
    }

    Vec3D operator-(double s) const
    {
        return {x - s, y - s, z - s};
    }

    Vec3D &operator-=(Vec3D const &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec3D &operator-=(double s)
    {
        x -= s;
        y -= s;
        z -= s;
        return *this;
    }

    Vec3D operator*(Vec3D const &v) const
    {
        return {x * v.x, y * v.y, z * v.z};
    }

    Vec3D operator*(double s) const
    {
        return {x * s, y * s, z * s};
    }

    Vec3D &operator*=(Vec3D const &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vec3D &operator*=(double s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    Vec3D operator/(Vec3D const &v) const
    {
        return {x / v.x, y / v.y, z / v.z};
    }

    Vec3D operator/(double s) const
    {
        return {x / s, y / s, z / s};
    }

        Vec3D &operator/=(Vec3D const &v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vec3D &operator/=(double s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    Vec3D pow(double e) const
    {
        return {std::pow(x, e), std::pow(y, e), std::pow(z, e)};
    }
};

class Color {
public:
    double r;
    double g;
    double b;

    Color() : r(0.0), g(0.0), b(0.0) {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}

    Color operator+(Color const &v) const
    {
        return {r + v.r, g + v.g, b + v.b};
    }

    Color operator+(double s) const
    {
        return {r + s, g + s, b + s};
    }

    Color &operator+=(Color const &v)
    {
        r += v.r;
        g += v.g;
        b += v.b;
        return *this;
    }

    Color &operator+=(double s)
    {
        r += s;
        g += s;
        b += s;
        return *this;
    }

    Color operator-(Color const &v) const
    {
        return {r - v.r, g - v.g, b - v.b};
    }

    Color operator-(double s) const
    {
        return {r - s, g - s, b - s};
    }

    Color &operator-=(Color const &v)
    {
        r -= v.r;
        g -= v.g;
        b -= v.b;
        return *this;
    }

    Color &operator-=(double s)
    {
        r -= s;
        g -= s;
        b -= s;
        return *this;
    }

    Color operator*(Color const &v) const
    {
        return {r * v.r, g * v.g, b * v.b};
    }

    Color operator*(double s) const
    {
        return {r * s, g * s, b * s};
    }

    Color &operator*=(Color const &v)
    {
        r *= v.r;
        g *= v.g;
        b *= v.b;
        return *this;
    }

    Color &operator*=(double s)
    {
        r *= s;
        g *= s;
        b *= s;
        return *this;
    }

    Color operator/(Color const &v) const
    {
        return {r / v.r, g / v.g, b / v.b};
    }

    Color operator/(double s) const
    {
        return {r / s, g / s, b / s};
    }

        Color &operator/=(Color const &v)
    {
        r /= v.r;
        g /= v.g;
        b /= v.b;
        return *this;
    }

    Color &operator/=(double s)
    {
        r /= s;
        g /= s;
        b /= s;
        return *this;
    }

    Color pow(double e) const
    {
        return {std::pow(r, e), std::pow(g, e), std::pow(b, e)};
    }
};

} // namespace Ameth
