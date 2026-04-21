/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** main
*/

#include "DLLoader/DLLoader.hpp"
#include "plugins/IPrimitive.hpp"

int main()
{
   DLLoader<IPrimitive> loader("build/libsphere.so");
}
