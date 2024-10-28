#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <cmath>

// Chaque opération attend deux vecteurs avec valeurs x, y, z -> v1 et v2 par exemple
// Format d'utilisation : v1.operation(v2)
// Si besoin d'afficher des valeurs vous pouvez utiliser la fonction .afficher()


class Vector3D {
private:
    float x, y, z;

public:
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3D addition(const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D substraction(const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3D multiplyByScalar(float k) const {
        return Vector3D(x * k, y * k, z * k);
    }

    Vector3D normalize() const {
        float len = length();
        if (len == 0) return Vector3D(0, 0, 0); 
        return multiplyByScalar(1.0f / len);
    }

    float projectionOn(const Vector3D& a) const {
        Vector3D a_normalized = a.normalize();
        return (x * a_normalized.x + y * a_normalized.y + z * a_normalized.z);
    }

    Vector3D projectOn(const Vector3D& a) const {
        float proj_length = projectionOn(a);
        Vector3D a_normalized = a.normalize();
        return a_normalized.multiplyByScalar(proj_length);
    }

    void display() const {
        std::cout << "Vecteur: (" << x << ", " << y << ", " << z << ")\n";
    }
};

#endif 