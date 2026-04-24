/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Scene
*/

#pragma once
#include "plugins/IPrimitive.hpp"
#include "plugins/ILight.hpp"
#include "plugins/IMaterial.hpp"
#include "Camera/Camera.hpp"
#include <memory>
namespace RayTracer
{
    class Scene {
        public:
            Scene(/* Camera &cam, */
                std::vector<std::unique_ptr<IPrimitive>> primitives
                // std::vector<std::unique_ptr<ILight>> &Lights,
                // std::vector<std::unique_ptr<IMaterial>> &materials
                );

            std::vector<Ameth::Color> getScreen();

        private:
            Camera _camera;
            std::vector<std::unique_ptr<IPrimitive>> _primitives;
            std::vector<std::unique_ptr<ILight>> _lights;
            std::vector<std::unique_ptr<IMaterial>> _materials;

            Ameth::Color _hitColor;

            bool rayHitPrimitive(Camera::Ray &ray);
    };
}
