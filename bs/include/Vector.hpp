/*
** EPITECH PROJECT, 2026
** vector3D
** File description:
** 
*/

#ifndef VECTOR3D
    #define VECTOR3D
#include <exception>


namespace Math {
    class DivideByZero : public std::exception
    {
        public :
            const char *what() const noexcept override {
                return "[Math] Try to Divide by 0";
            }
    };

    class Vector3D
    {
    public:
        double x;
        double y;
        double z;

        Vector3D(double x, double y = 0, double z = 0);
        Vector3D() = default;
        ~Vector3D() = default;

        double length();
        double dot(Vector3D oth);
        Vector3D normalize();

        Vector3D operator+(Vector3D oth);
        void operator+=(Vector3D oth);
        Vector3D operator-(Vector3D oth);
        void operator-=(Vector3D oth);
        Vector3D operator*(double mult);
        Vector3D operator*(Vector3D oth);
        void operator*=(double mult);
        void operator*=(Vector3D oth);
        Vector3D operator/(double div);
        void operator/=(double div);
        Vector3D operator/(Vector3D oth) = delete;
        void operator/=(Vector3D oth) = delete;

    };
}

#endif