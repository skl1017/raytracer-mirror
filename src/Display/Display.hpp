/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Display
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <algorithm>
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
    void update(const std::vector<Ameth::Vector3D> hdrImage);
    std::vector<Ameth::Vector3D> loadHDRTestSample(double height, double width);
    bool savePPM(const std::string &path) const;

private:
    static constexpr double _gamma = 2.2;

    void toDisplaySpace(const std::vector<Ameth::Vector3D> hdrImage);
    void reinhardToneMap(Ameth::Vector3D &color);
    void applyGamma(Ameth::Vector3D &color);
    void putRGB(std::size_t pixelIndex, Ameth::Vector3D const &rgb);
    std::uint8_t toByteChannel(double channel);

    unsigned _width;
    unsigned _height;
    std::string _title;

    std::vector<std::uint8_t> _pixels;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::RenderWindow _window;
};
