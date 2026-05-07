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
        std::vector<std::unique_ptr<ILight>> lights;


        for (auto it = p.begin(); it != p.end(); it++){
            auto primitiveFunc = _lightsParsingFns.find(it->getName());
            if (primitiveFunc != _lightsParsingFns.end()){
                primitiveFunc->second(_dlloader, _pluginFactory, *it, lights);
            }
        }
        return lights;
    }

    void Parser::_parserGetPointLight(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &pointLights, std::vector<std::unique_ptr<ILight>>& primitivesList)
    {
        pluginManager.open("libs/Lights/libpointLight.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
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

    void Parser::_parserGetDirectionalLight(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &pointLights, std::vector<std::unique_ptr<ILight>>& primitivesList)
    {
        pluginManager.open("libs/Lights/libdirectionalLight.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
            "libs/Lights/libdirectionalLight.so", "registerPlugin"
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

            auto &directionToParse = s.lookup("direction");

            auto direction = Ameth::Vec3D(
                _parseDouble(directionToParse, "x"),
                _parseDouble(directionToParse, "y"),
                _parseDouble(directionToParse, "z")
            );

            PluginFactory::directionlight_payload_t lightPayload = {
                color, direction
            };
            primitivesList.push_back(pluginFactory.create("directionalLight", lightPayload));
        }
    }
}
