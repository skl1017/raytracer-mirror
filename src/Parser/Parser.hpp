/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Parser
*/

#pragma once
#include "Math/Ameth.hpp"
#include <variant>
#include "Scene/Scene.hpp"
#include <string>
#include <libconfig.h++>
#include <vector>
#include <memory>
#include "plugins/IPrimitive.hpp"
#include "plugins/ILight.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include "PluginsManager/PluginManager.hpp"
#include <map>
#include <functional>

namespace RayTracer
{
    class Parser
    {
        public:
            using RegisterPluginFn = void(*)(RayTracer::PluginFactory&);


            Parser(PluginManager&);
            Scene loadFile(const std::string &);
        private:
            PluginManager& _pluginManager;
            PluginFactory _pluginFactory;
            static double _parseDouble(libconfig::Setting &s, const std::string &);

            std::vector<std::unique_ptr<IPrimitive>> _parserGetPrimitives(libconfig::Setting &s);
            std::vector<std::unique_ptr<ILight>> _parserGetLights(libconfig::Setting &s);


            static void _parserGetSpheres(
                PluginManager &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&);
            static void _parserGetPlanes(
                PluginManager &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&);


            static void _parserGetPointLight(
                PluginManager &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<ILight>>&);

            std::map<std::string, std::function<void (PluginManager &
                ,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&)>> _primitivesParsingFns =
                {
                    {"spheres", _parserGetSpheres},
                    {"planes", _parserGetPlanes},
                };
            std::map<std::string, std::function<void (PluginManager &
                ,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<ILight>>&)>> _lightsParsingFns =
                {
                    {"point", _parserGetPointLight},
                    // {"planes", _parserGetPlanes},
                };

    };
}
