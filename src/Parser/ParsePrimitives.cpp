/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ParsePrimitives
*/

#include "Parser/Parser.hpp"

namespace RayTracer
{
    std::vector<std::unique_ptr<IPrimitive>> Parser::_parserGetPrimitives(libconfig::Setting &p)
    {
        std::vector<std::unique_ptr<IPrimitive>> primitives;


        for (auto it = p.begin(); it != p.end(); it++){
            auto primitiveFunc = _primitivesParsingFns.find(it->getName());
            if (primitiveFunc != _primitivesParsingFns.end()){
                primitiveFunc->second(_pluginManager, _pluginFactory, *it, primitives);
            }
        }
        return primitives;
    }

    void Parser::_parserGetPlanes(PluginManager &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &planes, std::vector<std::unique_ptr<IPrimitive>>& primitivesList)
    {
        pluginManager.primitiveLoader.open("libs/Primitives/libplane.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.primitiveLoader.sym(
                "libs/Primitives/libplane.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: planes)
        {
            auto &colorToParse = s.lookup("color");
            auto color = Ameth::Color(
                _parseDouble(colorToParse, "r"),
                _parseDouble(colorToParse, "g"),
                _parseDouble(colorToParse, "b")

            );
            std::string axis = s.lookup("axis");
            auto position = _parseDouble(s, "position");

            PluginFactory::plane_payload_t planePayload = {
                color, axis[0], position
            };
            primitivesList.push_back(pluginFactory.create("plane", planePayload));
        }
    }

    void Parser::_parserGetSpheres(PluginManager &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &spheres, std::vector<std::unique_ptr<IPrimitive>>& primitivesList)
    {
        pluginManager.primitiveLoader.open("libs/Primitives/libsphere.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.primitiveLoader.sym(
                "libs/Primitives/libsphere.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: spheres)
        {
            auto &colorToParse = s.lookup("color");
            auto color = Ameth::Color(
                _parseDouble(colorToParse, "r"),
                _parseDouble(colorToParse, "g"),
                _parseDouble(colorToParse, "b")

            );
            auto position = Ameth::Vec3D(
                _parseDouble(s, "x"),
                _parseDouble(s, "y"),
                _parseDouble(s, "z")
            );
            auto r = _parseDouble(s, "r");

            PluginFactory::sphere_payload_t spherePayload = {
                color, position, r
            };
            primitivesList.push_back(pluginFactory.create("sphere", spherePayload));
        }
    }
}
