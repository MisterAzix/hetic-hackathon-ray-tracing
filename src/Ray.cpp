#include "Ray.h"
#include <cstdlib> // Pour rand() et RAND_MAX

// Fonctionnement de la classe : 
// - Le constructeur initialise l'origine et la direction du rayon
// - reflect renvoie un rayon réfléchi à partir d'un point d'impact, de la normale de la surface, de la réflectivité et de la profondeur restante
// - le coeff de réflexion renvoie un rayon réfléchi avec une composante aléatoire pour simuler la rugosité d'une surface métallique 
// - la profondeur permet de limiter le nombre de réflexions pour éviter les boucles infinies, la profondeur se décrémente à chaque appel récursif, si la profondeur = 0 la récursion s'arrête


Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction.normalize()) {}

Ray Ray::reflect(const Vector3 &point, const Vector3 &normal, float reflectivity, int depth) const
{
    if (depth <= 0)
    {
        return Ray(point, Vector3(0, 0, 0));
    }

    Vector3 incident = direction;
    Vector3 reflected = incident - 2 * (normal.dot(incident)) * normal;

    if (reflectivity > 0.0f)
    {
        float randomX = ((float)rand() / RAND_MAX) * reflectivity;
        float randomY = ((float)rand() / RAND_MAX) * reflectivity;
        float randomZ = ((float)rand() / RAND_MAX) * reflectivity;
        reflected = reflected + Vector3(randomX, randomY, randomZ).normalize() * reflectivity;
    }

    return Ray(point, reflected.normalize());
}