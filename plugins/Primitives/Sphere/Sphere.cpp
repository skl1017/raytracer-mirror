#include "Sphere.hpp"
#include "plugins/IPrimitive.hpp"



extern "C" RayTracer::IPrimitive *create()
{
    return new RayTracer::Sphere();
}

extern "C" PLUGIN getLibType()
{
    return MATERIAL;
}
