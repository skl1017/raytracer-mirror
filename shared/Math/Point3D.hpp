# pragma once

#include "Vector3D.hpp"
#include <cmath>
#include <type_traits>

namespace Math {
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    class Point3D {
        public:
            Point3D() : x(0), y(0), z(0) {}
            Point3D(T argx, T argy, T argz) : x(argx), y(argy), z(argz) {}
            T x;
            T y;
            T z;
            Point3D operator+=(Vector3D<T> vector)
            {
                return Point3D((x + (vector.x / vector.length())), (y + (vector.y / vector.length())), (z + (vector.z / vector.length())));
            }
            ~Point3D() = default;
        private:
    };
}