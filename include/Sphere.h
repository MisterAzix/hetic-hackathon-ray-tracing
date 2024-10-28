#pragma once
#include "Vector3.h"
#include "Ray.h"

class Sphere
{
public:
    Vector3 center;
    float radius;

    Sphere(const Vector3 &center, float radius) : center(center), radius(radius) {}

    bool intersect(const Ray &ray, float &t) const
    {
        Vector3 oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return false;
        }
        else
        {
            t = (-b - std::sqrt(discriminant)) / (2.0f * a);
            return true;
        }
    }
};
