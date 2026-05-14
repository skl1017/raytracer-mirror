/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Matrix
*/

#pragma once


#include <array>
#include <iostream>

template <typename T>

struct Matrix
{
    using Matrix4 = std::array<std::array<T, 4>, 4>;
    Matrix4 matrix;

    Matrix(const Matrix4 & m) {
        matrix = m;
    }

    Matrix() : matrix({}) {}

    std::array<T, 4> operator[](int i) const{
        return matrix[i];
    }

    std::array<T, 4> &operator[](int i){
        return matrix[i];
    }

    Matrix operator+(const Matrix &m) const
    {
        Matrix newMatrix;


        for (int y = 0; y < 4; y++){
            for (int x = 0; x < 4; x++){
                T val = 0;
                for (int i = 0; i < 4; i++){
                    val += (matrix[y][i] * m[i][y]);
                }
                newMatrix[y][x] = val;
            }
        }
        return newMatrix;
    }

    friend std::ostream& operator << (std::ostream& os, const Matrix &m) {
        for (int y = 0; y < 4; y++){
            for (int x = 0; x < 4; x++){
                os << m[y][x] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};
