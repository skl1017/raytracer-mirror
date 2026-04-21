/*
** EPITECH PROJECT, 2026
** Rectangle
** File description:
** 
*/

#ifndef RECT
    #define RECT
    #include "Point3D.hpp"
    #include <exception>

class Rectangle
{
private:
    Math::Point3D _origin;
    Math::Vector3D bottom_side;
    Math::Vector3D left_side;
public:
    class OutofBorder : public std::exception 
    {
        const char* what() const noexcept override {
            return "[Rectangle] Try to access coordinate out of defined rectangle";
        }
    };

    Rectangle(Math::Point3D origin, Math::Vector3D bottom, Math::Vector3D left) :
        _origin(origin), bottom_side(bottom), left_side(left) {};
    ~Rectangle() = default;

    Math::Point3D pointAt(double u, double v) {
        if (u < 0 || v < 0 || u > 1 || v > 1){
            throw Rectangle::OutofBorder();
        }
        return _origin + (bottom_side * u) + (left_side * v);
    };
};

#endif