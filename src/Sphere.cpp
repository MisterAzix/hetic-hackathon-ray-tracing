#include "Sphere.h"
#include "Vector3.h"
#include "Color.h"
#include <cmath>

Sphere::Sphere(const Vector3 &center, const float radius, const Color& color) : center(center), radius(radius), color(color) {}

bool Sphere::intersect(const Ray &ray, float &t) const {
    Vector3 vectorOC = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * vectorOC.dot(ray.direction);
    float c = vectorOC.dot(vectorOC) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }
    t = (-b - std::sqrt(discriminant)) / (2.0f * a);
    return true;
}

Color Sphere::getColor() const {
    return color;
}

Vector3 Sphere::getNormal(const Vector3 &point) const {
    return (point - center).normalize();
}