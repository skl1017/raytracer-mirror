/*
** EPITECH PROJECT, 2026
** main
** File description:
** 
*/

#include "Camera.hpp"
#include "Sphere.hpp"
#include <iostream>

#define LENGTH 1000
#define WIDTH 1000

int main()
{
    RayTracer::Camera cam(Math::Vector3D(LENGTH, 0, 0), Math::Vector3D(0, WIDTH, 0));
    RayTracer::Sphere s(Math::Point3D(0, 0, -40), 39.9);
    std::cout << "P3" << std::endl << WIDTH << " " << LENGTH << std::endl << "255" << std::endl;
    for (double x = 0; x < LENGTH; x++) {
        for (double y = 0; y < WIDTH; y++) {
            double u = x / LENGTH;
            double v = y / WIDTH;
            RayTracer::Ray r = cam.ray(u, v);
            if (s.hits(r)) {
                std::cout << "255 0 0" << std::endl;
            } else {
                std::cout << "0 0 255" << std::endl;
            }
    }
    }
}