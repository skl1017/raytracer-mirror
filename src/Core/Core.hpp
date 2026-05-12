/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#pragma once

#include "Display/Display.hpp"
#include "Scene/Scene.hpp"
#include "DLLoader/DLLoader.hpp"
#include <exception>
#include <string>
#include <string_view>
#include "plugins/IRenderer.hpp"
#include "Renderer/NormalRenderer.hpp"
#include "Renderer/RaytracingRender.hpp"
#include "Math/Ameth.hpp"

namespace RayTracer
{
    class Core {
    public:
        explicit Core(const std::string &file);

        int run(std::string_view outputPath = "output.ppm");
        void handleEnvents(Display &display);

        DLLoader _dlloader;
        Scene _scene;
        std::size_t _select_renderer = 0;
        std::vector<std::unique_ptr<IRenderer>> _renderers;
        class CoreException : public std::exception {
        private:
            std::string _m;
        public:
            CoreException(const std::string &m) : _m(m) {}
            const char *what() const noexcept { return _m.c_str(); }
        };
    };
}
