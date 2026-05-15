/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Bounding volume hierarchy for IPrimitive
*/

#pragma once

#include "Math/Ameth.hpp"
#include "Ray/Ray.hpp"
#include "plugins/IPrimitive.hpp"

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace RayTracer {

struct BvhNode {
    Ameth::Vec3D aabbMin{};
    Ameth::Vec3D aabbMax{};
    bool isLeaf{true};
    std::uint32_t leftChild{0};
    std::uint32_t rightChild{0};
    std::vector<IPrimitive const *> primitives{};
};

class Bvh {
public:
    Bvh() = default;

    void build(std::vector<std::unique_ptr<IPrimitive>> const &primitives, unsigned maxPrimitivesPerLeaf = 2);
    bool hit(Ray const &ray, Ray::HitRecord &rec) const;
    bool empty() const noexcept { return _nodes.empty(); }
    std::vector<BvhNode> const &nodes() const noexcept { return _nodes; }

private:
    void subdivide(std::uint32_t nodeIdx, std::vector<IPrimitive const *> prims);
    void computeBounds(BvhNode &node, std::vector<IPrimitive const *> const &prims);
    std::pair<std::vector<IPrimitive const *>, std::vector<IPrimitive const *>>
        partitionByAxis(std::vector<IPrimitive const *> const &prims, int axis, double splitPos);
    void makeLeaf(BvhNode &node, std::vector<IPrimitive const *> prims);
    bool hitNode(std::uint32_t nodeIndex, Ray const &ray, double tMin, double tMax, Ray::HitRecord &rec) const;
    bool hitLeafPrimitives(BvhNode const &node, Ray const &ray, double tMin, Ray::HitRecord &rec) const;
    static bool clipSlab(double o, double d, double bLo, double bHi, double &tMin, double &tMax);
    static bool intersectAabb(Ray const &ray, BvhNode const &node, double tMin, double tMax);

    std::vector<BvhNode> _nodes{};
    std::uint32_t _nodesUsed{0};
    unsigned _maxLeaf{2};
};

} // namespace RayTracer
