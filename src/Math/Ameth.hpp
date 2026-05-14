#pragma once

#include <cmath>
#include <array>
#include <cstddef>
#include <cstdio>
#include <iostream>

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

    Vec3D cross(Vec3D const &b) const
    {
        return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
    }

    Vec3D normalized() const
    {
        double const len = length();
        if (len < 1e-12)
            return {0.0, 0.0, 1.0};
        return *this * (1.0 / len);
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

class Quaternion {
public:
    double x;
    double y;
    double z;
    double w;

    Quaternion()
        : x(0.0),
          y(0.0),
          z(0.0),
          w(1.0)
    {
    }

    Quaternion(double x, double y, double z, double w)
        : x(x),
          y(y),
          z(z),
          w(w)
    {
    }

    static Quaternion identity() noexcept
    {
        return Quaternion(0.0, 0.0, 0.0, 1.0);
    }

    static Quaternion angleAxis(double angle, Vec3D const &axis)
    {
        Vec3D const n = axis.normalized();
        double const h = 0.5 * angle;
        double const s = std::sin(h);
        return Quaternion(n.x * s, n.y * s, n.z * s, std::cos(h)).normalized();
    }

    double length() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Quaternion normalized() const
    {
        double const len = length();
        if (len < 1e-12)
            return identity();
        double const inv = 1.0 / len;
        return {x * inv, y * inv, z * inv, w * inv};
    }

    Quaternion operator*(Quaternion const &b) const
    {
        Vec3D const v1{x, y, z};
        Vec3D const v2{b.x, b.y, b.z};
        double const s1 = w;
        double const s2 = b.w;
        double const s = s1 * s2 - v1.dot(v2);
        Vec3D const v = v1 * s2 + v2 * s1 + v1.cross(v2);
        return {v.x, v.y, v.z, s};
    }

    Vec3D rotate(Vec3D const &v) const
    {
        Vec3D const u{x, y, z};
        Vec3D const t = u.cross(v) * 2.0;
        return v + t * w + u.cross(t);
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

template <typename T, int rows, int columns>
struct Matrix
{
    using MatrixContainer = std::array<std::array<T, columns>, rows>;
    MatrixContainer matrix;

    Matrix(const MatrixContainer &m) : matrix(m) {};

    Matrix() : matrix({}) {};

    const std::array<T, columns> &operator[](int i) const
    {
        return matrix[i];
    }

    std::array<T, columns> &operator[](int i)
    {
        return matrix[i];
    }

    Matrix operator+(const Matrix& m) const
    {
        Matrix newMatrix;
    
        for (size_t y = 0; y < rows; y++)
            for (size_t x = 0; x < columns; x++)
                newMatrix[y][x] = matrix[y][x] + m[y][x];
        return newMatrix;
    }

    Matrix operator*(const Matrix &m) const
    {
        Matrix newMatrix;

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                for (size_t a = 0; a < columns; a++) {
                    newMatrix[i][a] += (matrix[i][j] * m[j][a]);
                }
            }
        }
        return newMatrix;
    }

    friend std::ostream& operator << (std::ostream& os, const Matrix &m) {
        for (size_t y = 0; y < rows; y++){
            for (size_t x = 0; x < columns; x++){
                os << m[y][x] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

} // namespace Ameth
