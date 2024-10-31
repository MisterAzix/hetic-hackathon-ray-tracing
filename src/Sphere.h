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
    float reflectivity;

    Sphere(const Vector3 &center, float radius, const Color &color, float reflectivity = 0.0f);

    bool intersect(const Ray &ray, float &t) const override;

    Color getColor() const override;

    Vector3 getNormal(const Vector3 &point) const override;

    float getReflectivity() const override { return reflectivity; }
};