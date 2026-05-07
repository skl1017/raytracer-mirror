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
        try {
            libconfig::Config c = libconfig::Config();
            c.readFile(file.c_str());
            auto primitives = _parserGetPrimitives(c.lookup("primitives"));
            auto lights = _parserGetLights(c.lookup("lights"));
            auto cameras = _parserGetCameras(c.lookup("cameras"));
            return Scene(std::move(cameras),std::move(primitives), {}, std::move(lights));
        } catch (const libconfig::ParseException &e){
            std::cerr << e.getFile() << ": Parsing error at line " << e.getLine() << ": " << e.getError() << std::endl;
            throw e;
        }
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
