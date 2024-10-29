#pragma once
#include <cmath>

class Vector3
{
public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3 &v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3 &v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }

    Vector3 normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        return Vector3(x / length, y / length, z / length);
    }

    float dot(const Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }
};
