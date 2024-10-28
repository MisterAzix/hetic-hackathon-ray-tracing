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

};

