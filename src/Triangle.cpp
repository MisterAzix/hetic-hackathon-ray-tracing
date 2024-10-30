#include "Triangle.h"

Triangle::Triangle(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2)
    : v0(v0), v1(v1), v2(v2) {}

bool Triangle::intersect(const Ray &ray, float &distance) const
{
    const float tolerance = 1e-6;
    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;

    Vector3 hVector = ray.direction.cross(edge2);
    float determinant = edge1.dot(hVector);

    if (determinant > -tolerance && determinant < tolerance)
        return false;

    float inverseDet = 1.0 / determinant;
    Vector3 originToVertex = ray.origin - v0;
    float uCoord = inverseDet * originToVertex.dot(hVector);

    if (uCoord < 0.0 || uCoord > 1.0)
        return false;

    Vector3 qVector = originToVertex.cross(edge1);
    float vCoord = inverseDet * ray.direction.dot(qVector);

    if (vCoord < 0.0 || uCoord + vCoord > 1.0)
        return false;

    distance = inverseDet * edge2.dot(qVector);

    return distance > tolerance;
}
