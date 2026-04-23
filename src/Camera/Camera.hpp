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
        Ameth::Vec3D origin{};
        Ameth::Vec3D direction{};
    };

    Camera(unsigned imageWidth, unsigned imageHeight, Ameth::Vec3D edgeU, Ameth::Vec3D edgeV, double pinholeZ = 10.0);

    Ray ray(double u, double v) const;

    std::vector<Ameth::Color> &getHDRImage() { return _hdrImage; }
    std::vector<Ameth::Color> const &getHDRImage() const { return _hdrImage; }
    unsigned imageWidth() const { return _imageWidth; }
    unsigned imageHeight() const { return _imageHeight; }
    Ameth::Vec3D const &origin() const { return _origin; }

private:
    Ameth::Vec3D pointOnScreen(double u, double v) const;

    Ameth::Vec3D _origin{};
    Ameth::Vec3D _screenCorner{};
    Ameth::Vec3D _edgeU{};
    Ameth::Vec3D _edgeV{};
    unsigned _imageWidth{0};
    unsigned _imageHeight{0};
    std::vector<Ameth::Color> _hdrImage{};
};
