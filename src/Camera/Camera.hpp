/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Camera
*/

#pragma once

#include "Math/Ameth.hpp"

#include <cstddef>
#include <vector>

class Camera {
public:
    struct Ray {
        Ameth::Vector3D origin{};
        Ameth::Vector3D direction{};
    };

    Camera(unsigned imageWidth, unsigned imageHeight, Ameth::Vector3D edgeU, Ameth::Vector3D edgeV, double pinholeZ = 10.0);

    Ray ray(double u, double v) const;

    std::vector<Ameth::Vector3D> &getHDRImage() { return _hdrImage; }
    std::vector<Ameth::Vector3D> const &getHDRImage() const { return _hdrImage; }
    unsigned imageWidth() const { return _imageWidth; }
    unsigned imageHeight() const { return _imageHeight; }
    Ameth::Vector3D const &origin() const { return _origin; }

private:
    Ameth::Vector3D pointOnScreen(double u, double v) const;

    Ameth::Vector3D _origin{};
    Ameth::Vector3D _screenCorner{};
    Ameth::Vector3D _edgeU{};
    Ameth::Vector3D _edgeV{};
    unsigned _imageWidth{0};
    unsigned _imageHeight{0};
    std::vector<Ameth::Vector3D> _hdrImage{};
};
