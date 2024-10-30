#include "Square.h"

Square::Square(const Vector3 &center, float size, const Color& color)
    : center(center), size(size), normal(0, 0, 1), color(color) {}

bool Square::intersect(const Ray &ray, float &t) const
{
    if (ray.direction.z == 0)
    {
        return false;
    }

    t = (center.z - ray.origin.z) / ray.direction.z;

    if (t < 0)
    {
        return false;
    }

    Vector3 p = ray.origin + ray.direction * t;

    float halfSize = size / 2;
    if (p.x >= center.x - halfSize && p.x <= center.x + halfSize &&
        p.y >= center.y - halfSize && p.y <= center.y + halfSize)
    {
        return true;
    }

    return false;
}

Color Square::getColor() const
{
    return color;
}