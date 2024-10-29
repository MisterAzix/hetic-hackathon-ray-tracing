#pragma once
#include "Ray.h"

class Object
{
public:
    virtual bool intersect(const Ray &ray, float &t) const = 0;
    virtual ~Object() = default;
};