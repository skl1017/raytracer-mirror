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

    Scene Parser::loadFile(const std::string &file)
    {
        libconfig::Config c = libconfig::Config();
        c.readFile(file.c_str());

        auto primitives = _parserGetPrimitives(c.lookup("primitives"));
        return Scene(std::move(primitives));
    }

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
