/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Factory
*/

#pragma once
#include "Math/Ameth.hpp"
#include <variant>
#include <string>
#include <map>
#include <functional>
#include <memory>
#include "plugins/IPrimitive.hpp"
#include "Primitives/Sphere/Sphere.hpp"
#include "PluginsManager/PluginManager.hpp"
#include "plugins/ILight.hpp"

namespace RayTracer
{
    class PluginFactory {

        public:

            typedef struct primitive_payload_base_s
            {
                Ameth::Vec3D color;
            } primitive_payload_base_t;

            typedef struct sphere_payload_s : primitive_payload_base_t
            {
                Ameth::Vec3D position;
                double r;
            } sphere_payload_t;

            typedef struct plane_payload_s : primitive_payload_base_t
            {
                char axis;
                double position;
            } plane_payload_t;

            typedef struct pointlight_payload_s
            {
                Ameth::Vec3D pos;
                Ameth::Color color;
            } pointlight_payload_t;

            typedef struct directionlight_payload_s
            {
                Ameth::Vec3D direction;
                Ameth::Color color;
            } directionlight_payload_t;


            using lightPayload = std::variant<
                pointlight_payload_t,
                directionlight_payload_t
                >;

            using primitivePayload = std::variant<
                primitive_payload_base_t,
                sphere_payload_t,
                plane_payload_t>;

            using iPrimitiveCreateFunction = std::function<std::unique_ptr<IPrimitive> (const primitivePayload& p)>;

            using iLightCreateFunction = std::function<std::unique_ptr<ILight> (const lightPayload& p)>;


            void add(const std::string &, iPrimitiveCreateFunction);
            void add(const std::string &, iLightCreateFunction);
            std::unique_ptr<IPrimitive> createPrimitive(const std::string &, const primitivePayload &);


            class PluginFactoryException : public std::exception
            {
                private:
                    std::string _m;
                    public:
                    PluginFactoryException(const std::string &m):_m(m){}
                    const char *what() const noexcept {
                        return _m.c_str();
                    }
            };


            private:
                std::map<std::string, iPrimitiveCreateFunction> _fPrimitives;
                std::map<std::string, iLightCreateFunction> _fLight;
    };

}
