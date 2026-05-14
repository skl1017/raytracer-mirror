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
            auto position = _parseDouble(s, "position");
            auto rotation = _parseVec3D(s, "rotation");
            PluginFactory::plane_payload_t planePayload = {
                {primitiveMaterial->second, rotation}, position
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
            auto position = _parseVec3D(s, "position");
            auto r = _parseDouble(s, "r");
            PluginFactory::sphere_payload_t spherePayload = {
                {primitiveMaterial->second, {0, 0, 0}}, position, r
            };
            primitivesList.push_back(pluginFactory.create("sphere", spherePayload));
        }
    }

    void Parser::_parserGetCylinders(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &cylinders
        , std::vector<std::unique_ptr<IPrimitive>>& primitivesList, std::map<std::string, std::shared_ptr<IMaterial>> materials)
    {
        pluginManager.open("libs/Primitives/libcylinder.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
                "libs/Primitives/libcylinder.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: cylinders)
        {
            std::cout << "Cylinder" << std::endl;
            std::string materialName = s.lookup("material");
            auto primitiveMaterial = materials.find(materialName);

            if (primitiveMaterial == materials.end())
                throw;
            auto position = _parseVec3D(s, "position");
            auto rotation = _parseVec3D(s, "rotation");
            std::cout << position.x << std::endl;
            auto r = _parseDouble(s, "r");
            PluginFactory::cylinder_payload_t cylinderPayload = {
                {primitiveMaterial->second, rotation}, position, r
            };
            primitivesList.push_back(pluginFactory.create("cylinder", cylinderPayload));
        }
    }
    void Parser::_parserGetCones(DLLoader &pluginManager, PluginFactory & pluginFactory,libconfig::Setting &cones
        , std::vector<std::unique_ptr<IPrimitive>>& primitivesList, std::map<std::string, std::shared_ptr<IMaterial>> materials)
    {
        pluginManager.open("libs/Primitives/libcone.so");
        auto reg = reinterpret_cast<RegisterPluginFn>(pluginManager.sym(
                "libs/Primitives/libcone.so", "registerPlugin"
            ));
        reg(pluginFactory);

        for (auto &s: cones)
        {
            std::string materialName = s.lookup("material");
            auto primitiveMaterial = materials.find(materialName);

            if (primitiveMaterial == materials.end()){
                throw;
            }
            double angle = _parseDouble(s, "angle");

            auto position = _parseVec3D(s, "position");
            auto rotation = _parseVec3D(s, "rotation");
            PluginFactory::cone_payload_t conePayload = {
                {primitiveMaterial->second, rotation}, position, angle
            };
            primitivesList.push_back(pluginFactory.create("cone", conePayload));
        }
    }
}
