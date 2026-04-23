/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#pragma once

#include "Scene/Scene.hpp"
#include <string>
#include <exception>
#include "PluginsManager/PluginManager.hpp"
namespace RayTracer
{
    class Core {

        public:

            Core(const std::string &);

        private:
            PluginManager _pluginManager;
            Scene _scene;

        public:
            class CoreException : public std::exception {
                private:
                    std::string _m;
                public:
                    CoreException(const std::string &m):_m(m){}
                    const char *what() const noexcept {
                        return _m.c_str();
                    }
            };
    };
}
