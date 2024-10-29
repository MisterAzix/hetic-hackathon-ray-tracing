#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object
{
public:
    Vector3 center;
    float radius;

    Sphere(const Vector3 &center, float radius);

    bool intersect(const Ray &ray, float &t) const override;
};