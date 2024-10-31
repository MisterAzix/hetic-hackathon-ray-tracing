#include "Sphere.h"
#include "Vector3.h"
#include "Color.h"
#include <cmath>

Sphere::Sphere(const Vector3 &center, const float radius, const Color &color, float reflectivity) : center(center), radius(radius), color(color), reflectivity(reflectivity) {}

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

    float t0 = (-b - std::sqrt(discriminant)) / (2.0f * a);
    float t1 = (-b + std::sqrt(discriminant)) / (2.0f * a);

    if (t0 > 0.001f) {
        t = t0;
    } else if (t1 > 0.001f) {
        t = t1;
    } else {
        return false;
    }
    
    return true;
}
Color Sphere::getColor() const
{
    return color;
}

Color Sphere::getColorAt(const Vector3 &) const
{
    return getColor();
}

Vector3 Sphere::getNormal(const Vector3 &point) const
{
    return (point - center).normalize();
}
