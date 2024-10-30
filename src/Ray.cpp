#include "Ray.h"
#include <cstdlib>

Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction.normalize()) {}

Ray Ray::reflect(const Vector3 &point, const Vector3 &normal, float reflectivity) const
{
    Vector3 incident = direction;
    Vector3 reflected = incident - 2 * (normal.dot(incident)) * normal;

    // Ajout de la rugosité pour simuler la réflexion métallique
    if (reflectivity > 0.0f)
    {
        float randomX = ((float)rand() / RAND_MAX) * reflectivity;
        float randomY = ((float)rand() / RAND_MAX) * reflectivity;
        float randomZ = ((float)rand() / RAND_MAX) * reflectivity;
        reflected = reflected + Vector3(randomX, randomY, randomZ).normalize() * reflectivity;
    }

    return Ray(point, reflected.normalize());
}