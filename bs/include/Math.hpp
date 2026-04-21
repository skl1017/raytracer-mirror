/*
** EPITECH PROJECT, 2026
** math
** File description:
** 
*/

#ifndef MATH_HPP
    #define MATH_HPP
    #include <cmath>

namespace Math
{
    class Polynomial
    {
    public:
        static std::size_t nbResult(double a, double b, double c) {
            double delta = std::pow(b, 2) - 4 * a * c;
            
            if (delta < 0) {
                return 0;
            }
            return (delta == 0) ? 1 : 2;
        }

        
    };
}


#endif