/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ParseCameras
*/

#include "Parser/Parser.hpp"

namespace RayTracer
{
    std::vector<std::unique_ptr<Camera>> Parser::_parserGetCameras(libconfig::Setting &p)
    {
        std::vector<std::unique_ptr<Camera>> cameras;


        for (auto const &c: p){
            auto &positionToParse = c.lookup("position");
            auto position = Ameth::Vec3D(
                _parseDouble(positionToParse, "x"),
                _parseDouble(positionToParse, "y"),
                _parseDouble(positionToParse, "z")
            );

            auto &rotationToParse = c.lookup("rotation");
            auto rotation = Ameth::Quaternion(
                _parseDouble(rotationToParse, "x"),
                _parseDouble(rotationToParse, "y"),
                _parseDouble(rotationToParse, "z"),
                _parseDouble(rotationToParse, "w")
            );

            auto &fov = c.lookup("fieldOfView");
            auto &w = c.lookup("resolution").lookup("width");
            auto &h = c.lookup("resolution").lookup("height");

            auto camera = std::make_unique<Camera>(
                position, rotation, fov, w, h
            );
            cameras.push_back(std::move(camera));
        }
        return cameras;
    }
}
