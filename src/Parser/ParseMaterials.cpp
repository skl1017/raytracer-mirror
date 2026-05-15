/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ParseMaterials
*/

#include "Parser/Parser.hpp"

#include <string>

namespace RayTracer
{
    std::map<std::string, std::shared_ptr<IMaterial>> Parser::_parserGetMaterials(libconfig::Setting &s)
    {
        std::map<std::string, std::shared_ptr<IMaterial>> materials;

        for (auto it = s.begin(); it != s.end(); it++){
            auto primitiveFunc = _materialsParsingFns.find(it->getName());
            if (primitiveFunc != _materialsParsingFns.end()){
                primitiveFunc->second(_dlloader, _pluginFactory, *it, materials);
            }
        }
        return materials;
    }

    void Parser::_parserGetFlatColor(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &material
        , std::map<std::string, std::shared_ptr<IMaterial>>& materialList)
    {
        pluginManager.open("libs/Materials/libflatColor.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
                "libs/Materials/libflatColor.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: material)
        {
            auto &colorToParse = s.lookup("color");
            auto color = Ameth::Color(
                _parseDouble(colorToParse, "r"),
                _parseDouble(colorToParse, "g"),
                _parseDouble(colorToParse, "b")

            );
            std::string const matName = static_cast<const char *>(s.lookup("name"));
            int const transparency = static_cast<int>(_parseDouble(s, "transparency"));
            int const reflection = s.exists("reflection") ? _parseDouble(s, "reflection") : 0.0;

            PluginFactory::flatColor_payload_t flatColorPayload = {
                color, transparency, reflection
            };
            materialList.insert({matName, pluginFactory.create("flatColor", flatColorPayload)});
        }
    }
}
