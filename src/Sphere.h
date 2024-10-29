#pragma once
#include "Vector3.h"
#include "Ray.h"

class Sphere
{
public:
    Vector3 center;
    float radius;

    Sphere(const Vector3 &center, float radius);

    bool intersect(const Ray &ray, float &t) const;
};