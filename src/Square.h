#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
#include "Color.h"

class Square : public Object
{
public:
    Vector3 center;
    float size;
    Vector3 normal;
    Color color;
    float reflectivity;

    Square(const Vector3 &center, float size, const Color &color, float reflectivity = 0.0f);

    bool intersect(const Ray &ray, float &t) const override;

    Color getColor() const override;

    Vector3 getNormal(const Vector3 &point) const override;

    float getReflectivity() const override { return reflectivity; }
};