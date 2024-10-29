#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Vector3 &center, const float radius) : center(center), radius(radius) {}

bool Sphere::intersect(const Ray &ray, float &t) const
{
    Vector3 vectorOC = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * vectorOC.dot(ray.direction);
    float c = vectorOC.dot(vectorOC) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return false;
    }
    t = (-b - std::sqrt(discriminant)) / (2.0f * a);
    return true;
}