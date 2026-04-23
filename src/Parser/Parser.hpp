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
            typedef struct primitive_payload_base_s
            {
                Ameth::Vector3D color;
            } primitive_payload_base_t;

            typedef struct sphere_payload_s : primitive_payload_base_t
            {
                Ameth::Vector3D position;
                double r;
            } sphere_payload_t;

            typedef struct plane_payload_s : primitive_payload_base_t
            {
                char axis;
                double position;
            } plane_payload_t;

            using primitivePayload = std::variant<
                primitive_payload_base_t,
                sphere_payload_t,
                plane_payload_t>;

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
