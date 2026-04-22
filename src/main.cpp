/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "PluginsManager/DLLoader.hpp"
#include "plugins/IPrimitive.hpp"
#include <functional>
#include <memory>
#include <iostream>

int main()
{
   DLLoader<RayTracer::IPrimitive> loader;
   loader.open("libs/Primitives/libsphere.so");
   std::function<PLUGIN()> getLibType = reinterpret_cast<PLUGIN(*)()>(loader.sym("libs/Primitives/libsphere.so", "getLibType"));
   std::cout << "Type: " << getLibType() << std::endl;
   auto sphere = loader.getInstance("libs/Primitives/libsphere.so", "create");
   std::cout << "Name: " << sphere->getName() << std::endl;
}
