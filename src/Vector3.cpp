#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3 &v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
Vector3 Vector3::operator-(const Vector3 &v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
Vector3 Vector3::operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }

float Vector3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vector3 Vector3::normalize() const
{
    float len = length();
    return Vector3(x / len, y / len, z / len);
}

float Vector3::dot(const Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }

Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x);
}

Vector3 operator*(float scalar, const Vector3 &v)
{
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}
