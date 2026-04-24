/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Camera
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Ray/Ray.hpp"

#include <cstddef>
#include <vector>

class Camera {
public:
    Camera(Ameth::Vec3D pos, Ameth::Quaternion rot, double fov, unsigned width, unsigned height);

    Ray ray(double u, double v) const;

    Ameth::Vec3D getGlobalPosition() const;
    Ameth::Quaternion getGlobalOrientation() const;

    void applyYaw(double yawDelta);
    void applyPitch(double pitchDelta);
    void applyRoll(double rollDelta);
    void moveForward(double speed);
    void strafeRight(double strafe);
    Ameth::Vec3D forward() const;
    Ameth::Vec3D right() const;

    std::vector<Ameth::Color> &getHDRImage() { return _hdrImage; }
    std::vector<Ameth::Color> const &getHDRImage() const { return _hdrImage; }
    unsigned imageWidth() const { return _imageWidth; }
    unsigned imageHeight() const { return _imageHeight; }

private:
    Ameth::Vec3D _position{};
    Ameth::Quaternion _orientation{Ameth::Quaternion::identity()};

    double _vfov{};
    unsigned _imageWidth{};
    unsigned _imageHeight{};
    double _aspect{};
    double _tanHalfVfov{};
    std::vector<Ameth::Color> _hdrImage{};
};
