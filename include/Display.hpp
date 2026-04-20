#pragma once

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "Ameth.hpp"

class Display {
public:
    Display(unsigned width, unsigned height, std::string title = "HDR view");

    bool create();
    bool isOpen() { return _window.isOpen(); }
    void pollEvents();
    void update();

    void putRgb01(std::size_t pixelIndex, Ameth::Vector3D const &rgb);

    static Ameth::Vector3D hdrTestSample(unsigned x, unsigned y, unsigned width, unsigned height);
    void toDisplaySpace(Ameth::Vector3D const &hdrLinear, std::size_t pixelIndex);
    bool savePPM(const std::string &path) const;

private:
    static constexpr double _gamma = 2.2;

    void reinhardToneMap(Ameth::Vector3D &color);
    void applyGamma(Ameth::Vector3D &color);
    std::uint8_t toByteChannel(double channel);

    unsigned _width;
    unsigned _height;
    std::string _title;

    std::vector<std::uint8_t> _pixels;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::RenderWindow _window;
};
