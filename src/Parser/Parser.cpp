/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Parser
*/

#include "Parser/Parser.hpp"

#include <stdexcept>
#include <string>

namespace RayTracer
{
    Parser::Parser(DLLoader &pluginManager):_dlloader(pluginManager){}

    Scene Parser::loadFile(const std::string &file)
    {
        libconfig::Config c;
        try {
            c.readFile(file.c_str());
            auto materials = _parserGetMaterials(c.lookup("materials"));
            auto primitives = _parserGetPrimitives(c.lookup("primitives"), materials);
            auto lights = _parserGetLights(c.lookup("lights"));
            auto cameras = _parserGetCameras(c.lookup("cameras"));
            return Scene(std::move(cameras), std::move(primitives), std::move(materials), std::move(lights));
        } catch (libconfig::ParseException const &ex) {
            throw std::runtime_error(
                std::string("parse error ") + ex.getFile() + ":" + std::to_string(ex.getLine()) + ": " + ex.getError());
        } catch (libconfig::FileIOException const &ex) {
            throw std::runtime_error(std::string("cannot read ") + file + ": " + ex.what());
        } catch (libconfig::SettingException const &ex) {
            throw std::runtime_error(std::string("setting ") + ex.getPath() + ": " + ex.what());
        }
    }

    double Parser::_parseDouble(libconfig::Setting &s, const std::string &key)
    {
        libconfig::Setting &v = s.lookup(key);
        if (v.getType() == libconfig::Setting::TypeInt)
            return static_cast<double>(static_cast<int>(v));
        if (v.getType() == libconfig::Setting::TypeInt64)
            return static_cast<double>(static_cast<long long>(v));
        return static_cast<double>(static_cast<float>(v));
    }

    Ameth::Vec3D Parser::_parseVec3D(libconfig::Setting &s, const std::string &key)
    {
        libconfig::Setting &g = s.lookup(key);
        return Ameth::Vec3D(
            _parseDouble(g, "x"),
            _parseDouble(g, "y"),
            _parseDouble(g, "z"));
    }
}
