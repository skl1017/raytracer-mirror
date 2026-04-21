# pragma once

#include <cmath>
#include <type_traits>

namespace Math {
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    class Vector3D {
        public:
            Vector3D() : x(0), y(0), z(0) {}
            Vector3D(T argx, T argy, T argz) : x(argx), y(argy), z(argz) {}
            T length()
            {
                return (std::sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
            }
            T dot(Vector3D<T> vector)
            {
                return ((x * vector.x) + (y * vector.y) + (z * vector.z));
            }
            ~Vector3D() = default;
            T x;
            T y;
            T z;
        private:
    };

}