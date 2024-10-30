#include "Ray.h"
#include <random>


// Fonctionnement de la classe : 
// - Le constructeur initialise l'origine et la direction du rayon
// - reflect renvoie un rayon réfléchi à partir d'un point d'impact, de la normale de la surface, de la réflectivité et de la profondeur restante
// - le coeff de réflexion renvoie un rayon réfléchi avec une composante aléatoire gaussienne pour simuler la rugosité d'une surface métallique 
// - la profondeur permet de limiter le nombre de réflexions pour éviter les boucles infinies, la profondeur se décrémente à chaque appel récursif, si la profondeur = 0 la récursion s'arrête


Ray::Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction.normalize()) {}

Ray Ray::reflect(const Vector3 &point, const Vector3 &normal, float reflectivity, int depth) const
{
    if (depth <= 0)
    {
        return Ray(point, Vector3(0, 0, 0)); // Retourne un rayon "nul" si la profondeur est atteinte
    }

    Vector3 incident = direction;
    Vector3 reflected = incident - 2 * (normal.dot(incident)) * normal;

    if (reflectivity > 0.0f)
    {
        // Initialisation du générateur aléatoire et de la distribution gaussienne
        static std::mt19937 rng(std::random_device{}());
        std::normal_distribution<float> dist(0.0f, reflectivity); // Moyenne de 0, écart-type défini par la rugosité

        Vector3 gaussianDeviation(dist(rng), dist(rng), dist(rng));
        
        reflected = (reflected + gaussianDeviation).normalize();
    }

    return Ray(point, reflected);
}

// Exemple d'utilisation : 

// // Initialisation du rayon incident
//     Vector3 origin(0, 0, 0);                 
//     Vector3 direction(1, -1, 0);             
//     Ray incidentRay(origin, direction);       

//     // Définition des paramètres pour la réflexion
//     Vector3 impactPoint(1, 1, 0);             
//     Vector3 surfaceNormal(0, 1, 0);           
//     float reflectivity = 0.5f;                
//     int maxDepth = 3;                         

//     // Appel à la méthode reflect pour calculer le rayon réfléchi
//     Ray reflectedRay = incidentRay.reflect(impactPoint, surfaceNormal, reflectivity, maxDepth);