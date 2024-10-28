#pragma once
#include "Vector3.h"
#include "Ray.h"

class Plane
{
public:
    Vector3 point;  // Un point sur le plan
    Vector3 normal; // La normale au plan

    Plane(const Vector3 &point, const Vector3 &normal) : point(point), normal(normal.normalize()) {}

    bool intersect(const Ray &ray, float &t) const
    {
        float denom = normal.dot(ray.direction);
        if (std::abs(denom) > 1e-6)
        { // Pour éviter les divisions par zéro
            Vector3 p0l0 = point - ray.origin;
            t = p0l0.dot(normal) / denom;
            return (t >= 0);
        }
        return false;
    }
};
