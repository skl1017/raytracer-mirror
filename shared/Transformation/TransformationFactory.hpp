#pragma once

#include "Math/Ameth.hpp"
#include <cmath>
#include <functional>

//using rotationFunction = std::function<Ameth::Matrix<double, 4, 4>(double angle)>;
class TransformationFactory {
    public:
        static Ameth::Matrix<double, 4, 4> getXRotation(double angle)
        {
            Ameth::Matrix<double, 4, 4> xRotation({{
                {1, 0, 0, 0},
                {0, std::cos(angle), -std::sin(angle), 0},
                {0, std::sin(angle), std::cos(angle), 0},
                {0, 0, 0, 1}}}
            );
            return xRotation;
        }

        static Ameth::Matrix<double, 4, 4> getYRotation(double angle)
        {
            Ameth::Matrix<double, 4, 4> yRotation({{
                {std::cos(angle), 0, std::sin(angle), 0},
                {0, 1, 0, 0},
                {-std::sin(angle), 0, std::cos(angle), 0},
                {0, 0,0,1}
            }});
            return yRotation;
        }

        static Ameth::Matrix<double, 4, 4> getZRotation(double angle)
        {
            Ameth::Matrix<double, 4, 4> zRotation({{
                {std::cos(angle),-std::sin(angle),0,0},
                {std::sin(angle),std::cos(angle),0,0},
                {0,0,1,0},
                {0,0,0,1}
            }});
            return zRotation;
        }  
};