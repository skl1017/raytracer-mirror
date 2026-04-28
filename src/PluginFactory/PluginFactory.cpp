/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Factory
*/

#include "PluginFactory.hpp"
namespace RayTracer
{
    void PluginFactory::add(const std::string &primitive, iPrimitiveCreateFunction func)
    {
        _fPrimitives[primitive] = func;
        return;
    }

    void PluginFactory::add(const std::string &light, iLightCreateFunction func)
    {
        _fLights[light] = func;
        return;
    }

    std::unique_ptr<IPrimitive> PluginFactory::create(const std::string &name, const primitivePayload &p)
    {
        auto func = _fPrimitives.find(name);
        if (func == _fPrimitives.end()){
            throw PluginFactoryException("No Plugin found for " + name);
        }
        return func->second(p);
    }
    std::unique_ptr<ILight> PluginFactory::create(const std::string &name, const lightPayload &p)
    {

        auto func = _fLights.find(name);
        if (func == _fLights.end()){
            throw PluginFactoryException("No Plugin found for " + name);
        }
        return func->second(p);
    }
}
