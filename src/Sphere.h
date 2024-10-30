#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
#include "Color.h"

class Sphere : public Object
{
public:
    Vector3 center;
    float radius;
    Color color;

    Sphere(const Vector3 &center, float radius, const Color &color);

    bool intersect(const Ray &ray, float &t) const override;

    Color getColor() const override;

    Vector3 getNormal(const Vector3 &point) const override;

    Color getColorAt(const Vector3 &) const override;
};