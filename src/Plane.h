#pragma once
#include "Vector3.h"
#include "Ray.h"
#include <cmath>

class Plane
{
public:
    Vector3 point;
    Vector3 normal;

    Plane(const Vector3 &point, const Vector3 &normal);

    bool intersect(const Ray &ray, float &t) const;
};