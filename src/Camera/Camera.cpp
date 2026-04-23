/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Camera
*/

#include "Camera/Camera.hpp"

#include <algorithm>

Camera::Camera(unsigned imageWidth, unsigned imageHeight, Ameth::Vec3D edgeU, Ameth::Vec3D edgeV,
    double pinholeZ)
    : _origin{0.0, 0.0, pinholeZ},
      _screenCorner(edgeU * (-0.5) + edgeV * (-0.5)),
      _edgeU(edgeU),
      _edgeV(edgeV),
      _imageWidth(imageWidth),
      _imageHeight(imageHeight),
      _hdrImage(static_cast<std::size_t>(imageWidth) * imageHeight)
{
}

Ameth::Vec3D Camera::pointOnScreen(double u, double v) const
{
    double uu = std::clamp(u, 0.0, 1.0);
    double vv = std::clamp(v, 0.0, 1.0);
    return _screenCorner + _edgeU * uu + _edgeV * vv;
}

Camera::Ray Camera::ray(double u, double v) const
{
    Ameth::Vec3D at = pointOnScreen(u, v);
    Ameth::Vec3D dir = at - _origin;
    return Ray{_origin, dir};
}
