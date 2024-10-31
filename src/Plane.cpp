#include "cmath"
#include "Plane.h"
#include "Color.h"
#include "Vector3.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, const Color &color, float reflectivity)
    : point(point), normal(normal.normalize()), color(color), reflectivity(reflectivity) {}

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
    Vector3 center(0, 0, 0);
    float distanceFromCenter = std::sqrt((hit_point.x - center.x) * (hit_point.x - center.x) +
                                         (hit_point.z - center.z) * (hit_point.z - center.z));

    float ringWidth = 5.0f;
    float lineThickness = 0.1f;
    float maxDistance = 6 * ringWidth; // Limite aux six premiers anneaux

    // Vérifie si le point est dans la portée des six premiers anneaux
    if (distanceFromCenter > maxDistance)
    {
        return Color(0.0f, 0.0f, 0.0f); // Couleur noire pour les zones en dehors des six premiers anneaux
    }

    // Vérifie si le point se trouve dans une bande "ligne" ou "espace"
    bool isLine = (distanceFromCenter - std::floor(distanceFromCenter / ringWidth) * ringWidth) < lineThickness;
    return isLine ? Color(1.0f, 1.0f, 1.0f) : Color(0.0f, 0.0f, 0.0f);
}

Vector3 Plane::getNormal(const Vector3 &point) const
{
    return normal;
}
