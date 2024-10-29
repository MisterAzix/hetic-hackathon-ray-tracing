#include "Vector3.h"
#include "cmath"

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3 &v) const { return {x + v.x, y + v.y, z + v.z}; }
Vector3 Vector3::operator-(const Vector3 &v) const { return {x - v.x, y - v.y, z - v.z}; }
Vector3 Vector3::operator*(const float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

Vector3 Vector3::normalize() const
{
    const float length = std::sqrt(x * x + y * y + z * z);
    return {x / length, y / length, z / length};
}

float Vector3::dot(const Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }