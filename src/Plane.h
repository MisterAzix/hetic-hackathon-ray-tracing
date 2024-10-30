#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
#include "Color.h"
#include <cmath>

class Plane : public Object
{
public:
    Vector3 point;
    Vector3 normal;
    Color color;

    Plane(const Vector3 &point, const Vector3 &normal, const Color& color);

    bool intersect(const Ray &ray, float &t) const override;

    Color getColor() const override;
};