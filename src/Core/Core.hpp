/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#pragma once

#include "Display/Display.hpp"
#include "Renderer/ParallelImageScheduler.hpp"
#include "Scene/Scene.hpp"
#include "DLLoader/DLLoader.hpp"
#include <SFML/Window/Event.hpp>
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
        void handleEnvents(Display &display, std::unique_ptr<Camera> &camera);

    private:
        static constexpr double _moveSpeed = 10.0;
        static constexpr double _rotationSpeed = 0.003;

        bool handleKeys(sf::Event &event, std::unique_ptr<Camera> &camera);
        bool handleMouse(sf::Event &event, std::unique_ptr<Camera> &camera);

        DLLoader _dlloader;
        Scene _scene;
        std::size_t _select_renderer = 0;
        std::vector<std::unique_ptr<IRenderer>> _renderers;
        ParallelImageScheduler _scheduler;

        bool _mouseLookActive = false;
        bool _mouseLookInitialized = false;
        int _lastMouseX = 0;
        int _lastMouseY = 0;

        class CoreException : public std::exception {
            private:
                std::string _m;
            public:
                CoreException(const std::string &m) : _m(m) {}
                const char *what() const noexcept { return _m.c_str(); }
        };
    };
}
