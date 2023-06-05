//
// Created by arlev on 06.06.2023.
//

#include "BvhNode.h"

bool BvhNode::hit(const Ray &ray, float tMin, float tMax, HitRecord &hit) const
{
    if(box.hit(ray, tMin, tMax))
    {
        const auto leftHit = left->hit(ray, tMin, tMax, hit);
        const auto rightHit = right->hit(ray, tMin, leftHit ? hit.t : tMax, hit);

        return leftHit || rightHit;
    }

    return false;
}

bool BvhNode::boundingBox(double t0, double t1, AABB &outBox) const
{
    outBox = box;
    return true;
}
