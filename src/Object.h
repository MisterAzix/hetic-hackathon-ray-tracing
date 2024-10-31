#pragma once
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"

class Object
{
public:
    virtual bool intersect(const Ray &ray, float &t) const = 0;

    virtual Color getColor() const = 0;

    virtual Color getColorAt(const Vector3 &hit_point) const { return getColor(); }

    virtual Vector3 getNormal(const Vector3 &point) const = 0;

    virtual ~Object() = default;

    float reflectivity = 0.0f;
    virtual float getReflectivity() const { return reflectivity; }
};
