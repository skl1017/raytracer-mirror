/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Factory
*/

#include "PluginFactory.hpp"

namespace RayTracer
{
    void PluginFactory::add(const std::string &primitive, primtiveCreateFunction f)
    {
        _fPrimitives[primitive] = f;
        return;
    }
    std::unique_ptr<IPrimitive> PluginFactory::createPrimitive(const std::string &name, const primitivePayload &p)
    {
        auto f = _fPrimitives.find(name);
        if (f == _fPrimitives.end()){
            throw PluginFactoryException("No Plugin found for " + name);
        }
        return f->second(p);
    }
}
