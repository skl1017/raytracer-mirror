/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Core
*/

#include "Core.hpp"
#include "Math/Ameth.hpp"
#include <libconfig.h++>
#include "Parser/Parser.hpp"
#include "plugins/IPrimitive.hpp"
namespace RayTracer
{
    Core::Core(const std::string &file):_pluginManager({
        DLLoader<IPrimitive>()
    }),
    _scene([&](){
        Parser parser(_pluginManager);
        return parser.loadFile(file);
    }()){}

}
