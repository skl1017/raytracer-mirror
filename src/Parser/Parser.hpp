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
#include "PluginFactory/PluginFactory.hpp"
#include "PluginsManager/PluginManager.hpp"

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
            double _parseDouble(libconfig::Setting &s, const std::string &);
            std::vector<std::unique_ptr<IPrimitive>> _parserGetPrimitives(libconfig::Setting &s);
            void _parserGetSpheres(libconfig::Setting &s, std::vector<std::unique_ptr<IPrimitive>>&);

    };
}
