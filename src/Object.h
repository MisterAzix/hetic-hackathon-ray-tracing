#pragma once
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"

class Object {
public:
    virtual bool intersect(const Ray &ray, float &t) const = 0;
    virtual Color getColor() const = 0;
    virtual Vector3 getNormal(const Vector3 &point) const = 0;
    virtual ~Object() = default;
};