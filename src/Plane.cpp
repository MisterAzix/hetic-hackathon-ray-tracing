#include "cmath"
#include "Plane.h"
#include "Color.h"
#include "Vector3.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, const Color& color) : point(point), normal(normal.normalize()), color(color) {}

bool Plane::intersect(const Ray &ray, float &t) const {
    float denom = normal.dot(ray.direction);
    if (std::abs(denom) > 1e-6) {
        Vector3 p0l0 = point - ray.origin;
        t = p0l0.dot(normal) / denom;
        return (t >= 0);
    }
    return false;
}

Color Plane::getColor() const {
    return color;
}

Vector3 Plane::getNormal(const Vector3 &point) const {
    return normal;
}