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

    Camera(Ameth::Vector3D pos, Ameth::Quaternion rot, double fov, unsigned width, unsigned height);

    Ray ray(double u, double v) const;

    Ameth::Vector3D getGlobalPosition() const;
    Ameth::Quaternion getGlobalOrientation() const;

    void applyYaw(double yawDelta);
    void applyPitch(double pitchDelta);
    void applyRoll(double rollDelta);
    void moveForward(double speed);
    void strafeRight(double strafe);
    Ameth::Vector3D forward() const;
    Ameth::Vector3D right() const;

    std::vector<Ameth::Vector3D> &getHDRImage() { return _hdrImage; }
    std::vector<Ameth::Vector3D> const &getHDRImage() const { return _hdrImage; }
    unsigned imageWidth() const { return _imageWidth; }
    unsigned imageHeight() const { return _imageHeight; }

private:
    Ameth::Vector3D _position{};
    Ameth::Quaternion _orientation{Ameth::Quaternion::identity()};

    double _vfov{};
    unsigned _imageWidth{};
    unsigned _imageHeight{};
    double _aspect{};
    double _tanHalfVfov{};
    std::vector<Ameth::Vector3D> _hdrImage{};
};
