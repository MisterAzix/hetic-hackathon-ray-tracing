#include "Vector3.h"

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::addition(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::substraction(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

float Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::multiplyByScalar(float k) const {
    return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::normalize() const {
    float len = length();
    if (len == 0) return Vector3(0, 0, 0);
    return multiplyByScalar(1.0f / len);
}

float Vector3::projectionOn(const Vector3& a) const {
    Vector3 a_normalized = a.normalize();
    return (x * a_normalized.x + y * a_normalized.y + z * a_normalized.z);
}

Vector3 Vector3::projectOn(const Vector3& a) const {
    float proj_length = projectionOn(a);
    Vector3 a_normalized = a.normalize();
    return a_normalized.multiplyByScalar(proj_length);
}

void Vector3::display() const {
    std::cout << "Vecteur: (" << x << ", " << y << ", " << z << ")\n";
}