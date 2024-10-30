#include "Ray.h"

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction.normalize()) {}

Ray Ray::reflect(const Vector3 &point, const Vector3 &normal) const
{
    Vector3 incident = direction;
    Vector3 reflected = incident - 2 * (normal.dot(incident)) * normal;
    return Ray(point, reflected.normalize());
}