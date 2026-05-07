/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** test DLLoader
*/

#include <cassert>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "Primitives/Sphere/Sphere.hpp"
#include "plugins/IPrimitive.hpp"

// Test(DLLoader, load_one_lib)
// {
//     DLLoader<IPrimitive> loader;

//     loader.open("libs/Primitives/libsphere.so");
//     std::function<PLUGIN()> getLibType = reinterpret_cast<PLUGIN(*)()>(loader.sym("libs/Primitives/libsphere.so", "getLibType"));
//     cr_assert_eq(PRIMITIVE, getLibType());
// };

// Test(DLLoader, load_different_lib)
// {
//     DLLoader<IPrimitive> loader;

//     loader.open("libs/Primitives/libsphere.so");
//     auto sphere = loader.getInstance("libs/Primitives/libsphere.so", "create");
//     cr_assert_eq(sphere->getName(), "Sphere");
// }

// Test(DLLoader, load_same_lib)
// {
//     DLLoader<IPrimitive> loader;

//     loader.open("libs/Primitives/libsphere.so");
//     auto sphere = loader.getInstance("libs/Primitives/libsphere.so", "create");
//     loader.open("libs/Primitives/libsphere.so");
//     auto sphere_two = loader.getInstance("libs/Primitives/libsphere.so", "create");
//     cr_assert_eq(sphere->getName(), "Sphere");
// }
