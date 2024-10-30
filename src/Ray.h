#pragma once
#include "Vector3.h"

// Pour calculer le rayon réfléchi, renseigner le point d'impact et la normale de la surface 
class Ray
{
public:
    Vector3 origin, direction;

    Ray(const Vector3 &origin, const Vector3 &direction);

    Ray reflect(const Vector3 &point, const Vector3 &normal, float reflectivity, int depth) const;
};