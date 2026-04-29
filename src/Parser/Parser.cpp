/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Parser
*/

#include "Parser/Parser.hpp"
#include <iostream>

namespace RayTracer
{
    Parser::Parser(PluginManager &pluginManager):_pluginManager(pluginManager){}

    void Parser::_parserGetSpheres(libconfig::Setting &spheres, std::vector<std::unique_ptr<IPrimitive>>& primitivesList)
    {
        _pluginManager.primitiveLoader.open("libs/Primitives/libsphere.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(_pluginManager.primitiveLoader.sym(
                "libs/Primitives/libsphere.so", "registerPlugin"
            ));
        reg(_pluginFactory);

        for (auto &s: spheres)
        {

            auto position = Ameth::Vec3D(
                _parseDouble(s, "x"),
                _parseDouble(s, "y"),
                _parseDouble(s, "z")
            );
            auto r = _parseDouble(s, "r");

            PluginFactory::sphere_payload_t spherePayload = {
                {{0, 0, 0}}, position, r
            };
            primitivesList.push_back(_pluginFactory.createPrimitive("sphere", spherePayload));
        }

    }

    std::vector<std::unique_ptr<IPrimitive>> Parser::_parserGetPrimitives(libconfig::Setting &p)
    {
        std::vector<std::unique_ptr<IPrimitive>> primitives;

        if (p.exists("spheres")){
            auto &spheres = p.lookup("spheres");
            _parserGetSpheres(spheres, primitives);
        }
        return primitives;
    }


    // Scene Parser::loadFile(const std::string &file)
    // {
    //     libconfig::Config c = libconfig::Config();
    //     c.readFile(file.c_str());

    //     auto primitives = _parserGetPrimitives(c.lookup("primitives"));
    //     return Scene(std::move(primitives));
    // }

    double Parser::_parseDouble(libconfig::Setting &s, const std::string &key)
    {
        double x;
        try {
            x = s.lookup(key);
        } catch (const libconfig::SettingTypeException &e){
            x = int(s.lookup(key));
        }

        return x;
    }

}
