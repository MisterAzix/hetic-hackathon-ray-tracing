#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "Object.h"
#include "Color.h"

class Plane : public Object
{
public:
    Vector3 point;
    Vector3 normal;
    Color color;

    Plane(const Vector3 &point, const Vector3 &normal, const Color &color);

    bool intersect(const Ray &ray, float &t) const override;

    Color getColor() const override;

    Color getColorAt(const Vector3 &hit_point) const override;

    Vector3 getNormal(const Vector3 &point) const override;

    Color getCheckerboardColor(const Vector3 &hit_point) const;
};