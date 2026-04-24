/*
** EPITECH PROJECT, 2026
** Camera
** File description:
** Camera
*/

#include "Camera/Camera.hpp"

#include <algorithm>
#include <cmath>

Camera::Camera(Ameth::Vec3D pos, Ameth::Quaternion rot, double fov, unsigned width, unsigned height)
    : _position(pos),
      _orientation(rot),
      _vfov(fov),
      _imageWidth(width),
      _imageHeight(height),
      _aspect(static_cast<double>(width) / static_cast<double>(height)),
      _tanHalfVfov(std::tan(fov * 0.5)),
      _hdrImage(static_cast<std::size_t>(width) * height)
{
}

void Camera::applyYaw(double yawDelta)
{
    Ameth::Vec3D const y = _orientation.rotate({0.0, 1.0, 0.0});
    Ameth::Quaternion const yawQ = Ameth::Quaternion::angleAxis(yawDelta, y);
    _orientation = (yawQ * _orientation).normalized();
}

void Camera::applyPitch(double pitchDelta)
{
    Ameth::Vec3D const x = _orientation.rotate({1.0, 0.0, 0.0});
    Ameth::Quaternion const pitchQ = Ameth::Quaternion::angleAxis(pitchDelta, x);
    _orientation = (pitchQ * _orientation).normalized();
}

void Camera::applyRoll(double rollDelta)
{
    Ameth::Vec3D const f = _orientation.rotate({0.0, 0.0, 1.0});
    Ameth::Quaternion const rollQ = Ameth::Quaternion::angleAxis(rollDelta, f);
    _orientation = (rollQ * _orientation).normalized();
}

void Camera::moveForward(double speed)
{
    _position += forward() * speed;
}

void Camera::strafeRight(double strafe)
{
    _position += right() * strafe;
}

Ameth::Vec3D Camera::forward() const
{
    return _orientation.rotate({0.0, 0.0, 1.0});
}

Ameth::Vec3D Camera::right() const
{
    return _orientation.rotate({1.0, 0.0, 0.0});
}

Ameth::Vec3D Camera::getGlobalPosition() const
{
    return _position;
}

Ameth::Quaternion Camera::getGlobalOrientation() const
{
    return _orientation;
}

Ray Camera::ray(double u, double v) const
{
    double x = (2.0 * u - 1.0) * _aspect * _tanHalfVfov;
    double y = (1.0 - 2.0 * v) * _tanHalfVfov;
    Ameth::Vec3D localDir(x, y, 1.0);
    Ameth::Vec3D dirW = _orientation.rotate(localDir).normalized();
    return Ray{_position, dirW};
}
