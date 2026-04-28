/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ParseLights
*/

#include "Parser/Parser.hpp"

namespace RayTracer
{
    std::vector<std::unique_ptr<ILight>> Parser::_parserGetLights(libconfig::Setting &p)
    {
        std::vector<std::unique_ptr<ILight>> primitives;


        for (auto it = p.begin(); it != p.end(); it++){
            auto primitiveFunc = _lightsParsingFns.find(it->getName());
            if (primitiveFunc != _lightsParsingFns.end()){
                primitiveFunc->second(_pluginManager, _pluginFactory, *it, primitives);
            }
        }
        return primitives;
    }

    void Parser::_parserGetPointLight(PluginManager &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &pointLights, std::vector<std::unique_ptr<ILight>>& primitivesList)
    {
        pluginManager.primitiveLoader.open("libs/Lights/libpointLight.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.primitiveLoader.sym(
                "libs/Lights/libpointLight.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: pointLights)
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

            PluginFactory::pointlight_payload_t spherePayload = {
                color, position
            };
            primitivesList.push_back(pluginFactory.create("pointLight", spherePayload));
        }
    }
}
