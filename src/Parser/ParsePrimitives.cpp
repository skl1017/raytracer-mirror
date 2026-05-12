/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** ParsePrimitives
*/

#include "Parser/Parser.hpp"

namespace RayTracer
{
    std::vector<std::unique_ptr<IPrimitive>> Parser::_parserGetPrimitives(libconfig::Setting &p, std::map<std::string, std::shared_ptr<IMaterial>> materials)
    {
        std::vector<std::unique_ptr<IPrimitive>> primitives;


        for (auto it = p.begin(); it != p.end(); it++){
            auto primitiveFunc = _primitivesParsingFns.find(it->getName());
            if (primitiveFunc != _primitivesParsingFns.end()){
                primitiveFunc->second(_dlloader, _pluginFactory, *it, primitives, materials);
            }
        }
        return primitives;
    }

    void Parser::_parserGetPlanes(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &planes
        , std::vector<std::unique_ptr<IPrimitive>>& primitivesList, std::map<std::string, std::shared_ptr<IMaterial>> materials)
    {
        pluginManager.open("libs/Primitives/libplane.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
                "libs/Primitives/libplane.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: planes)
        {
            std::string materialName = s.lookup("material");
            auto primitiveMaterial = materials.find(materialName);

            if (primitiveMaterial == materials.end()){
                throw;
            }

            std::string axis = s.lookup("axis");
            auto position = _parseDouble(s, "position");

            PluginFactory::plane_payload_t planePayload = {
                {primitiveMaterial->second}, axis[0], position
            };
            primitivesList.push_back(pluginFactory.create("plane", planePayload));
        }
    }

    void Parser::_parserGetSpheres(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &spheres
        , std::vector<std::unique_ptr<IPrimitive>>& primitivesList, std::map<std::string, std::shared_ptr<IMaterial>> materials)
    {
        pluginManager.open("libs/Primitives/libsphere.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
                "libs/Primitives/libsphere.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: spheres)
        {

             std::string materialName = s.lookup("material");
            auto primitiveMaterial = materials.find(materialName);

            if (primitiveMaterial == materials.end()){
                throw;
            }

            auto position = Ameth::Vec3D(
                _parseDouble(s, "x"),
                _parseDouble(s, "y"),
                _parseDouble(s, "z")
            );
            auto r = _parseDouble(s, "r");

            PluginFactory::sphere_payload_t spherePayload = {
                {primitiveMaterial->second}, position, r
            };
            primitivesList.push_back(pluginFactory.create("sphere", spherePayload));
        }
    }
}
