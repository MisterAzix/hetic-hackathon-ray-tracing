#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"

class Square : public Object
{
public:
    Vector3 center;
    float size;
    Vector3 normal;

    Square(const Vector3 &center, float size);

    bool intersect(const Ray &ray, float &t) const;
};
