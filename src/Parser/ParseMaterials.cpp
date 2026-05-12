/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ParseMaterials
*/

#include "Parser/Parser.hpp"

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
            auto &name = s.lookup("name");
            int transparency = s.lookup("transparency");

            PluginFactory::flatColor_payload_t flatColorPayload = {
                color, transparency
            };
            materialList.insert({name, pluginFactory.create("flatColor", flatColorPayload)});
        }
}



}
