/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Display
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Math/Ameth.hpp"

class Display {
public:
    Display(unsigned width, unsigned height, std::string title = "HDR view");

    bool create();
    bool isOpen() { return _window.isOpen(); }
    void pollEvents();
    void update(const std::vector<Ameth::Color> hdrImage);
    std::vector<Ameth::Color> loadHDRTestSample(double height, double width);
    bool savePPM(const std::string &path) const;

private:
    static constexpr double _gamma = 2.2;

    void toDisplaySpace(const std::vector<Ameth::Color> hdrImage);
    void reinhardToneMap(Ameth::Color &color);
    void applyGamma(Ameth::Color &color);
    void putRGB(std::size_t pixelIndex, const Ameth::Color &color);
    std::uint8_t toByteChannel(double channel);

    unsigned _width;
    unsigned _height;
    std::string _title;

    std::vector<std::uint8_t> _pixels;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::RenderWindow _window;
};
