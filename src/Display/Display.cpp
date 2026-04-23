/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Display
*/

#include "Display/Display.hpp"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <utility>
#include <vector>

Display::Display(unsigned width, unsigned height, std::string title)
    : _width(width),
      _height(height),
      _title(std::move(title)),
      _pixels(width * height * 4)
{
}

bool Display::create()
{
    if (!_texture.create(_width, _height))
        return false;

    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(_width), static_cast<int>(_height)));

    _window.create(sf::VideoMode(_width, _height), _title);
    return _window.isOpen();
}

void Display::pollEvents()
{
    sf::Event event{};
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void Display::update(const std::vector<Ameth::Color> hdrImage)
{
    Display::toDisplaySpace(hdrImage);
    _texture.update(_pixels.data());
    _window.clear();
    _window.draw(_sprite);
    _window.display();
}

void Display::putRGB(std::size_t pixelIndex, const Ameth::Color &color)
{
    std::size_t colorIndex = pixelIndex * 4;
    _pixels[colorIndex + 0] = toByteChannel(color.r);
    _pixels[colorIndex + 1] = toByteChannel(color.g);
    _pixels[colorIndex + 2] = toByteChannel(color.b);
    _pixels[colorIndex + 3] = 255;
}

void Display::reinhardToneMap(Ameth::Color &color)
{
    color /= (color + 1.0);
}

void Display::applyGamma(Ameth::Color &color)
{
    color = color.pow(1.0 / _gamma);
}

void Display::loadHDRTestSample(std::vector<Ameth::Color> &hdrImage)
{
    for (unsigned y = 0; y < _height; ++y) {
        for (unsigned x = 0; x < _width; ++x) {
            std::size_t pixelIndex = std::size_t(y) * _width + x;
            double xd = static_cast<double>(x);
            double yd = static_cast<double>(y);
            double widthd = static_cast<double>(_width);
            double heightd = static_cast<double>(_height);
            hdrImage[pixelIndex] = Ameth::Color(2.0 * xd / widthd, 2.0 * yd / heightd, 0.35);
        }
    }
}

std::uint8_t Display::toByteChannel(double channel)
{
    channel = std::clamp(static_cast<int>(channel * 255.0), 0, 255);
    return static_cast<std::uint8_t>(channel);
}

void Display::toDisplaySpace(const std::vector<Ameth::Color> hdrImage)
{
    for (unsigned y = 0; y < _height; ++y) {
        for (unsigned x = 0; x < _width; ++x) {
            std::size_t pixelIndex = std::size_t(y) * _width + x;
            Ameth::Color color = hdrImage[pixelIndex];
            reinhardToneMap(color);
            applyGamma(color);
            putRGB(pixelIndex, color);
        }
    }
}

bool Display::savePPM(const std::string &path) const
{
    std::ofstream out(path, std::ios::binary);
    if (!out)
        return false;
    out << "P6\n" << _width << ' ' << _height << "\n255\n";
    for (std::size_t i = 0; i < _width * _height; ++i) {
        std::size_t const colorIndex = i * 4;
        out.put(static_cast<char>(_pixels[colorIndex + 0]));
        out.put(static_cast<char>(_pixels[colorIndex + 1]));
        out.put(static_cast<char>(_pixels[colorIndex + 2]));
    }
    return true;
}
