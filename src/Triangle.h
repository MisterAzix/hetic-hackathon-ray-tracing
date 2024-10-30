#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"

class Triangle : public Object
{
public:
    Vector3 v0, v1, v2;

    Triangle(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2);

    bool intersect(const Ray &ray, float &t) const;
};
