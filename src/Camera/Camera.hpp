/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Camera
*/

#pragma once

#include "Math/Ameth.hpp"
#include "plugins/IMaterial.hpp"

#include <cstddef>
#include <memory>
#include <vector>

class Camera {
public:
    struct Ray {
        Ameth::Vec3D origin{};
        Ameth::Vec3D direction{};
        Ameth::Vec3D at(double t) const { return origin + direction * t; }
    };

    struct HitRecord {
        double t{};
        Ameth::Vec3D point{};
        Ameth::Vec3D normal{};
        double u{};
        double v{};
        std::shared_ptr<IMaterial> material{};
    };

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
