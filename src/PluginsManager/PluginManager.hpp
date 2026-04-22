/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DLLoader
*/

#pragma once

#include "DLLoader.hpp"
#include "plugins/IPrimitive.hpp"

struct PluginManager {
    DLLoader<IPrimitive> primitiveLoader;
};

