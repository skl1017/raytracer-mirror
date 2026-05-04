/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#pragma once

#include "Scene/Scene.hpp"
#include "PluginsManager/PluginManager.hpp"
#include <exception>
#include <string>
#include <string_view>

namespace RayTracer
{
    class Core {
    public:
        explicit Core(const std::string &file);
        // Core(Scene scene);

        // static Core createDemo();
        int run(std::string_view outputPath = "output.ppm");

        PluginManager _pluginManager;
        Scene _scene;

        class CoreException : public std::exception {
        private:
            std::string _m;

        public:
            CoreException(const std::string &m) : _m(m) {}
            const char *what() const noexcept { return _m.c_str(); }
        };
    };
}
