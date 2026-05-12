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
#include "DLLoader/DLLoader.hpp"
#include "PluginFactory/PluginFactory.hpp"
#include "Camera/Camera.hpp"
#include <map>
#include <functional>

namespace RayTracer
{
    class Parser
    {
        public:
            using RegisterPluginFn = void(*)(RayTracer::PluginFactory&);


            Parser(DLLoader&);
            Scene loadFile(const std::string &);
        private:
            DLLoader& _dlloader;
            PluginFactory _pluginFactory;
            static double _parseDouble(libconfig::Setting &s, const std::string &);

            std::vector<std::unique_ptr<IPrimitive>> _parserGetPrimitives(libconfig::Setting &s);
            std::vector<std::unique_ptr<ILight>> _parserGetLights(libconfig::Setting &s);
            std::vector<std::unique_ptr<Camera>> _parserGetCameras(libconfig::Setting &s);

            static void _parserGetSpheres(
                DLLoader &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&);
            static void _parserGetPlanes(
                DLLoader &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&);


            static void _parserGetPointLight(
                DLLoader &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<ILight>>&);
            static void _parserGetDirectionalLight(
                DLLoader &,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<ILight>>&);

            std::map<std::string, std::function<void (DLLoader &
                ,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&)>> _primitivesParsingFns =
                {
                    {"spheres", _parserGetSpheres},
                    {"planes", _parserGetPlanes},
                };
            std::map<std::string, std::function<void (DLLoader &
                ,PluginFactory &,libconfig::Setting &s, std::vector<std::unique_ptr<ILight>>&)>> _lightsParsingFns =
                {
                    {"point", _parserGetPointLight},
                    {"directional", _parserGetDirectionalLight},
                };

    };
}
