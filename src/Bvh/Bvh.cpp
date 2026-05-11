/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** Bounding volume hierarchy for IPrimitive
*/

#include "Bvh/Bvh.hpp"

#include <algorithm>
#include <cmath>
#include <memory>

namespace RayTracer {

bool Bvh::clipSlab(double o, double d, double bLo, double bHi, double &tMin, double &tMax)
{
    constexpr double eps = 1e-12;
    if (std::abs(d) < eps)
        return o >= bLo && o <= bHi;
    double invD = 1.0 / d;
    double t0 = (bLo - o) * invD;
    double t1 = (bHi - o) * invD;
    if (invD < 0.0)
        std::swap(t0, t1);
    if (t0 > tMin)
        tMin = t0;
    if (t1 < tMax)
        tMax = t1;
    return tMax > tMin;
}

bool Bvh::intersectAabb(Ray const &ray, BvhNode const &node, double tMin, double tMax)
{
    if (!clipSlab(ray.origin.x, ray.direction.x, node.aabbMin.x, node.aabbMax.x, tMin, tMax))
        return false;
    if (!clipSlab(ray.origin.y, ray.direction.y, node.aabbMin.y, node.aabbMax.y, tMin, tMax))
        return false;
    if (!clipSlab(ray.origin.z, ray.direction.z, node.aabbMin.z, node.aabbMax.z, tMin, tMax))
        return false;
    return true;
}

void Bvh::computeBounds(BvhNode &node, std::vector<IPrimitive const *> const &prims)
{
    node.aabbMin = { 1e30,  1e30,  1e30};
    node.aabbMax = {-1e30, -1e30, -1e30};
    for (IPrimitive const *p : prims) {
        Ameth::Aabb const b = p->boundingBox();
        node.aabbMin.x = std::min(node.aabbMin.x, b.min.x);
        node.aabbMin.y = std::min(node.aabbMin.y, b.min.y);
        node.aabbMin.z = std::min(node.aabbMin.z, b.min.z);
        node.aabbMax.x = std::max(node.aabbMax.x, b.max.x);
        node.aabbMax.y = std::max(node.aabbMax.y, b.max.y);
        node.aabbMax.z = std::max(node.aabbMax.z, b.max.z);
    }
}

std::pair<std::vector<IPrimitive const *>, std::vector<IPrimitive const *>>
Bvh::partitionByAxis(std::vector<IPrimitive const *> const &prims, int axis, double splitPos)
{
    std::vector<IPrimitive const *> left;
    std::vector<IPrimitive const *> right;
    left.reserve(prims.size());
    right.reserve(prims.size());
    for (IPrimitive const *p : prims) {
        Ameth::Aabb const b = p->boundingBox();
        Ameth::Vec3D const cent = (b.min + b.max) * 0.5;
        if (cent[axis] < splitPos)
            left.push_back(p);
        else
            right.push_back(p);
    }
    return {std::move(left), std::move(right)};
}

void Bvh::makeLeaf(BvhNode &node, std::vector<IPrimitive const *> prims)
{
    node.isLeaf = true;
    node.primitives = std::move(prims);
}

void Bvh::subdivide(std::uint32_t nodeIdx, std::vector<IPrimitive const *> prims)
{
    BvhNode &node = _nodes[nodeIdx];
    computeBounds(node, prims);
    if (prims.size() <= _maxLeaf) {
        makeLeaf(node, std::move(prims));
        return;
    }
    Ameth::Vec3D const extent = node.aabbMax - node.aabbMin;
    int axis = 0;
    if (extent[1] > extent[0])
        axis = 1;
    if (extent[2] > extent[axis])
        axis = 2;
    double const splitPos = node.aabbMin[axis] + extent[axis] * 0.5;
    auto [leftPrims, rightPrims] = partitionByAxis(prims, axis, splitPos);
    if (leftPrims.empty() || rightPrims.empty()) {
        makeLeaf(node, std::move(prims));
        return;
    }
    std::uint32_t const leftIdx = _nodesUsed++;
    std::uint32_t const rightIdx = _nodesUsed++;
    node.isLeaf = false;
    node.leftChild = leftIdx;
    node.rightChild = rightIdx;
    subdivide(leftIdx, std::move(leftPrims));
    subdivide(rightIdx, std::move(rightPrims));
}

void Bvh::build(std::vector<std::unique_ptr<IPrimitive>> const &primitives, unsigned maxPrimitivesPerLeaf)
{
    _maxLeaf = std::max(1u, maxPrimitivesPerLeaf);
    _nodes.clear();
    _nodesUsed = 0;
    if (primitives.empty())
        return;
    std::uint32_t const poolSize = static_cast<std::uint32_t>(2 * primitives.size() - 1);
    _nodes.assign(poolSize, BvhNode{});
    _nodesUsed = 1;
    std::vector<IPrimitive const *> rootPrims;
    rootPrims.reserve(primitives.size());
    for (auto const &p : primitives)
        rootPrims.push_back(p.get());
    subdivide(0, std::move(rootPrims));
    _nodes.resize(_nodesUsed);
}

bool Bvh::hitLeafPrimitives(BvhNode const &node, Ray const &ray, double tMin, Ray::HitRecord &rec) const
{
    bool hitAnything = false;
    for (IPrimitive const *p : node.primitives) {
        Ray::HitRecord temp{};
        if (p->hit(ray, temp) && temp.t > tMin && temp.t < rec.t) {
            rec = temp;
            hitAnything = true;
        }
    }
    return hitAnything;
}

bool Bvh::hitNode(std::uint32_t nodeIndex, Ray const &ray, double tMin, double tMax, Ray::HitRecord &rec) const
{
    BvhNode const &node = _nodes[nodeIndex];
    if (!intersectAabb(ray, node, tMin, tMax))
        return false;
    if (node.isLeaf)
        return hitLeafPrimitives(node, ray, tMin, rec);
    bool const hitL = hitNode(node.leftChild, ray, tMin, tMax, rec);
    double const newTMax = hitL ? rec.t : tMax;
    bool const hitR = hitNode(node.rightChild, ray, tMin, newTMax, rec);
    return hitL || hitR;
}

bool Bvh::hit(Ray const &ray, Ray::HitRecord &rec) const
{
    if (_nodes.empty())
        return false;
    rec.t = std::numeric_limits<double>::infinity();
    return hitNode(0, ray, 1e-4, rec.t, rec);
}

} // namespace RayTracer
