#include "Display.hpp"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <utility>

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

void Display::update()
{
    _texture.update(_pixels.data());
    _window.clear();
    _window.draw(_sprite);
    _window.display();
}

void Display::putRGB(std::size_t pixelIndex, Ameth::Vector3D const &rgb)
{
    std::size_t colorIndex = pixelIndex * 4;
    _pixels[colorIndex + 0] = toByteChannel(rgb.x);
    _pixels[colorIndex + 1] = toByteChannel(rgb.y);
    _pixels[colorIndex + 2] = toByteChannel(rgb.z);
    _pixels[colorIndex + 3] = 255;
}

void Display::reinhardToneMap(Ameth::Vector3D &color)
{
    color /= (color + 1.0);
}

void Display::applyGamma(Ameth::Vector3D &color)
{
    color = color.pow(1.0 / _gamma);
}

Ameth::Vector3D Display::hdrTestSample(unsigned x, unsigned y, unsigned width, unsigned height)
{
    double xd = static_cast<double>(x);
    double yd = static_cast<double>(y);
    double widthd = static_cast<double>(width);
    double heightd = static_cast<double>(height);
    return Ameth::Vector3D(2.0 * xd / widthd, 2.0 * yd / heightd, 0.35);
}

std::uint8_t Display::toByteChannel(double channel)
{
    channel = std::clamp(static_cast<int>(channel * 255.0), 0, 255);
    return static_cast<std::uint8_t>(channel);
}

void Display::toDisplaySpace(Ameth::Vector3D const &hdrLinear, std::size_t pixelIndex)
{
    Ameth::Vector3D c = hdrLinear;
    reinhardToneMap(c);
    applyGamma(c);
    putRGB(pixelIndex, c);
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
