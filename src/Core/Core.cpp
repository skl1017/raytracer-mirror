/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#include "Core.hpp"
#include "Parser/Parser.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace RayTracer
{
    Core::Core(const std::string &file)
        : _dlloader({
              DLLoader(),
          }),
          _scene([&]() {
              Parser parser(_dlloader);
              return parser.loadFile(file);
          }()),
          _scheduler()
        {
            _renderers.push_back(std::make_unique<NormalRenderer>(Ameth::Color(0.2, 0.2, 0.2)));
            _renderers.push_back(std::make_unique<RaytracingRender>(Ameth::Color(0.2, 0.3, 0.9)));
        };

    bool Core::handleKeys(sf::Event &event, std::unique_ptr<Camera> &camera)
    {
        if (event.type != sf::Event::KeyPressed)
            return false;
        if (event.key.code == sf::Keyboard::Key::Tab) {
            _select_renderer = (_select_renderer + 1) % _renderers.size();
            return true;
        }
        if (event.key.code == sf::Keyboard::Key::Z || event.key.code == sf::Keyboard::Key::Up) {
            camera->moveForward(_moveSpeed);
            return true;
        }
        if (event.key.code == sf::Keyboard::Key::S || event.key.code == sf::Keyboard::Key::Down) {
            camera->moveForward(-_moveSpeed);
            return true;
        }
        if (event.key.code == sf::Keyboard::Key::Q || event.key.code == sf::Keyboard::Key::Left) {
            camera->strafeRight(-_moveSpeed);
            return true;
        }
        if (event.key.code == sf::Keyboard::Key::D || event.key.code == sf::Keyboard::Key::Right) {
            camera->strafeRight(_moveSpeed);
            return true;
        }
        return false;
    }

    bool Core::handleMouse(sf::Event &event, std::unique_ptr<Camera> &camera)
    {
        if (event.type == sf::Event::MouseButtonPressed
            && event.mouseButton.button == sf::Mouse::Right) {
            _mouseLookActive = true;
            _mouseLookInitialized = false;
            _lastMouseX = event.mouseButton.x;
            _lastMouseY = event.mouseButton.y;
            return false;
        }
        if (event.type == sf::Event::MouseButtonReleased
            && event.mouseButton.button == sf::Mouse::Right) {
            _mouseLookActive = false;
            return false;
        }
        if (event.type != sf::Event::MouseMoved || !_mouseLookActive)
            return false;
        if (!_mouseLookInitialized) {
            _lastMouseX = event.mouseMove.x;
            _lastMouseY = event.mouseMove.y;
            _mouseLookInitialized = true;
            return false;
        }
        int deltaX = event.mouseMove.x - _lastMouseX;
        int deltaY = event.mouseMove.y - _lastMouseY;
        _lastMouseX = event.mouseMove.x;
        _lastMouseY = event.mouseMove.y;
        if (deltaX == 0 && deltaY == 0)
            return false;
        camera->handleMouseLook(deltaX, deltaY, _rotationSpeed);
        return true;
    }

    void Core::handleEnvents(Display &display, std::unique_ptr<Camera> &camera)
    {
        sf::RenderWindow &window = display.getWindow();
        bool needsRender = false;

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                display.getWindow().close();
            needsRender |= handleMouse(event, camera);
            needsRender |= handleKeys(event, camera);
        }
        if (needsRender)
            _renderers[_select_renderer]->renderScreen(_scene, camera, _scheduler);
    }

    int Core::run(std::string_view outputPath)
    {
        _renderers[_select_renderer]->renderScreen(_scene, _scene._cameras[0], _scheduler);
        for (size_t index = 0; index < _scene._cameras.size(); ++index) {
            Display display(_scene._cameras[index]->imageWidth(), _scene._cameras[index]->imageHeight(), "raytracer");
            if (!display.create())
                throw std::runtime_error("Failed to create SFML window or texture");
            while (display.isOpen()) {
                handleEnvents(display, _scene._cameras[index]);
                display.update(_scene._cameras[index]->getHDRImage());
            }
            if (!display.savePPM(std::string(outputPath)))
                throw std::runtime_error("Failed to write " + std::string(outputPath));
        }
        return 0;
    }
}
