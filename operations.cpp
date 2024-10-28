#include <iostream>
#include <cmath>

class Vecteur3D {
private:
    float x, y, z;

public:
    Vecteur3D(float x, float y, float z) : x(x), y(y), z(z) {}

    Vecteur3D addition(const Vecteur3D& v) const {
        return Vecteur3D(x + v.x, y + v.y, z + v.z);
    }

    Vecteur3D soustraction(const Vecteur3D& v) const {
        return Vecteur3D(x - v.x, y - v.y, z - v.z);
    }

    float longueur() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vecteur3D multiplicationParScalaire(float k) const {
        return Vecteur3D(x * k, y * k, z * k);
    }

    Vecteur3D normaliser() const {
        float len = longueur();
        if (len == 0) return Vecteur3D(0, 0, 0); 
        return multiplicationParScalaire(1.0f / len);
    }

    float projectionSur(const Vecteur3D& a) const {
        Vecteur3D a_normalized = a.normaliser();
        return (x * a_normalized.x + y * a_normalized.y + z * a_normalized.z);
    }

    Vecteur3D projeterSur(const Vecteur3D& a) const {
        float proj_length = projectionSur(a);
        Vecteur3D a_normalized = a.normaliser();
        return a_normalized.multiplicationParScalaire(proj_length);
    }
};



