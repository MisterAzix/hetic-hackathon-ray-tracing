#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>

// Chaque opération attend deux vecteurs avec valeurs x, y, z -> v1 et v2 par exemple
// Format d'utilisation : v1.operation(v2)
// Si besoin d'afficher des valeurs vous pouvez utiliser la fonction .afficher()

class Vector3 {
private:
    float x, y, z;

public:
    Vector3(float x, float y, float z);

    Vector3 addition(const Vector3& v) const;
    Vector3 substraction(const Vector3& v) const;
    float length() const;
    Vector3 multiplyByScalar(float k) const;
    Vector3 normalize() const;
    float projectionOn(const Vector3& a) const;
    Vector3 projectOn(const Vector3& a) const;
    void display() const;
};

#endif // VECTOR3_H