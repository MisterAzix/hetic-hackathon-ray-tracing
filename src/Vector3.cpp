#include "Vector3.h"
#include "cmath"

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3 &v) const { return {x + v.x, y + v.y, z + v.z}; }
Vector3 Vector3::operator-(const Vector3 &v) const { return {x - v.x, y - v.y, z - v.z}; }
Vector3 Vector3::operator*(const float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
Vector3 operator*(float scalar, const Vector3 &v) {
    return {v.x * scalar, v.y * scalar, v.z * scalar};
}

Vector3 Vector3::normalize() const
{
    const float length = std::sqrt(x * x + y * y + z * z);
    return {x / length, y / length, z / length};
}

Vector3 Vector3::cross(const Vector3 &v) const {
    return {
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    };
}

float Vector3::dot(const Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }