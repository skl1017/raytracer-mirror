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
      _orientation(rot.normalized()),
      _vfov(fov),
      _imageWidth(width),
      _imageHeight(height),
      _aspect(static_cast<double>(width) / static_cast<double>(height)),
      _tanHalfVfov(std::tan((fov * M_PI / 180.0) * 0.5)),
      _hdrImage(static_cast<std::size_t>(width) * height)
{
    syncEulerFromOrientation();
}

void Camera::syncEulerFromOrientation()
{
    Ameth::Vec3D f = _orientation.rotate({0.0, 0.0, 1.0});
    _yaw = std::atan2(f.x, f.z);
    _pitch = std::asin(std::clamp(f.y, -1.0, 1.0));
    rebuildOrientationFromEuler();
}

void Camera::rebuildOrientationFromEuler()
{
    Ameth::Quaternion yawQ = Ameth::Quaternion::angleAxis(_yaw, {0.0, 1.0, 0.0});
    Ameth::Quaternion pitchQ = Ameth::Quaternion::angleAxis(_pitch, {1.0, 0.0, 0.0});
    _orientation = (yawQ * pitchQ).normalized();
}

void Camera::rotateView(double deltaYaw, double deltaPitch)
{
    _yaw += deltaYaw;
    _pitch = std::clamp(_pitch + deltaPitch, -kMaxPitch, kMaxPitch);
    rebuildOrientationFromEuler();
}

void Camera::handleMouseLook(int deltaX, int deltaY, double sensitivity)
{
    if (deltaX == 0 && deltaY == 0)
        return;
    rotateView(static_cast<double>(deltaX) * sensitivity, static_cast<double>(deltaY) * sensitivity);
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

Ameth::Vec3D Camera::up() const
{
    return _orientation.rotate({0.0, 1.0, 0.0});
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
