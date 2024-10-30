#pragma once
#include "Ray.h"
#include "Color.h"

class Object
{
public:
    virtual bool intersect(const Ray &ray, float &t) const = 0;
    virtual Color getColor() const = 0;
    virtual ~Object() = default;
};