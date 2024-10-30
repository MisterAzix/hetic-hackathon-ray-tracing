#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
#include "Color.h"

class Triangle : public Object
{
public:
    Vector3 v0, v1, v2;
    Color color;

    Triangle(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Color &color);

    bool intersect(const Ray &ray, float &t) const override;

    Color getColor() const override;

    Vector3 getNormal(const Vector3 &point) const override;
};