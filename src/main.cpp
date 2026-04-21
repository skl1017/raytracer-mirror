/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "DLLoader/DLLoader.hpp"
#include "plugins/IPrimitive.hpp"
#include <functional>
#include <iterator>
#include <memory>
#include <iostream>

int main()
{
   DLLoader<RayTracer::IPrimitive> loader("libs/Primitives/libsphere.so");
   loader.open();
   std::function<PLUGIN()> getLibType = reinterpret_cast<PLUGIN(*)()>(loader.sym("getLibType"));
   std::cout << "Type: " << getLibType() << std::endl;
   auto sphere = loader.getInstance("create");
   std::cout << "Name: " << sphere->getName() << std::endl;
}
