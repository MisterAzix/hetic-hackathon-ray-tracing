#include "cmath"
#include "Plane.h"
#include "Color.h"
#include "Vector3.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, const Color &color) : point(point), normal(normal.normalize()), color(color) {}

bool Plane::intersect(const Ray &ray, float &t) const
{
    float denom = normal.dot(ray.direction);
    if (std::abs(denom) > 1e-6)
    {
        Vector3 p0l0 = point - ray.origin;
        t = p0l0.dot(normal) / denom;
        return (t >= 0);
    }
    return false;
}

Color Plane::getColor() const
{
    return color;
}

Color Plane::getColorAt(const Vector3 &hit_point) const
{
    return getCheckerboardColor(hit_point);
}

Color Plane::getCheckerboardColor(const Vector3 &hit_point) const
{
    int checkerSize = 1;
    bool isBlack = (static_cast<int>(std::floor(hit_point.x / checkerSize) + std::floor(hit_point.z / checkerSize)) % 2) == 0;
    return isBlack ? Color(0.0f, 0.0f, 0.0f) : Color(1.0f, 1.0f, 1.0f);
}

Vector3 Plane::getNormal(const Vector3 &point) const
{
    return normal;
}