#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // Inclusion de la bibliothèque pour écrire des images PNG

#include "Vector3.h" // Inclusion du fichier de définition du vecteur 3D
#include "Ray.h"     // Inclusion du fichier de définition des rayons
#include "Sphere.h"  // Inclusion du fichier de définition des sphères
#include "Plane.h"   // Inclusion du fichier de définition des plans
#include "Scene.h"   // Inclusion du fichier de définition de la scène
#include <cstdlib>   // Inclusion de la bibliothèque standard pour rand
#include <algorithm> // Inclusion pour utiliser std::max et std::min

// Fonction d'atténuation de la lumière en fonction de la distance
float attenuation(float distance, float max_distance)
{
    // Retourne une valeur d'atténuation minimale de 0.1 pour éviter l'obscurcissement complet
    return std::max(0.1f, 1.0f - (distance / max_distance));
}

// Fonction pour vérifier si un point est dans l'ombre
bool isInShadow(const Vector3 &point, const Scene &scene, const Vector3 &light_position)
{
    Vector3 light_dir = (light_position - point).normalize(); // Calcul de la direction de la lumière
    Ray shadow_ray(point + light_dir * 0.001f, light_dir);    // Rayon légèrement décalé pour éviter les auto-ombres
    float t;
    int id;
    bool isSphere;
    // Vérifie si un objet bloque la lumière entre le point et la source lumineuse
    return scene.trace(shadow_ray, t, id, isSphere) && t < (light_position - point).length();
}

// Fonction de calcul de la couleur d'un rayon
Vector3 calculateColor(const Ray &ray, const Scene &scene, const Vector3 &light_position)
{
    float t;
    int id;
    bool isSphere;
    if (scene.trace(ray, t, id, isSphere)) // Si le rayon touche un objet
    {
        Vector3 hit_point = ray.origin + ray.direction * t;                                                       // Point d'impact
        Vector3 normal = isSphere ? (hit_point - scene.spheres[id].center).normalize() : scene.planes[id].normal; // Normale de la surface
        Vector3 light_dir = (light_position - hit_point).normalize();                                             // Direction de la lumière

        // Vérifie l'ombre seulement pour le sol (pas pour la sphère)
        bool shadow = isInShadow(hit_point, scene, light_position) && !isSphere;

        // Définit la couleur de l'objet (rouge pour la sphère, damier pour le sol)
        Vector3 object_color = isSphere ? Vector3(255, 0, 0) : scene.getCheckerboardColor(hit_point);

        // Calcul de la lumière diffuse avec atténuation d'ombre pour le sol uniquement
        float diff = std::max(0.0f, normal.dot(light_dir)) * (shadow ? 0.3f : 1.0f);

        // Calcul de la lumière spéculaire (éclat) si le point n'est pas en ombre
        Vector3 view_dir = -ray.direction.normalize();
        Vector3 half_dir = (light_dir + view_dir).normalize();
        float spec = std::pow(std::max(0.0f, normal.dot(half_dir)), 32) * (shadow ? 0.0f : 1.0f);

        // Calcul final de la couleur avec la lumière diffuse, spéculaire et atténuation en fonction de la distance
        float distance_to_light = (light_position - hit_point).length();
        float attenuation_factor = attenuation(distance_to_light, 20.0f);
        Vector3 final_color = (object_color * diff + Vector3(255, 255, 255) * spec) * attenuation_factor;

        return final_color; // Renvoie la couleur calculée pour le point
    }

    return Vector3(0, 0, 255); // Si aucun objet touché, retourne la couleur de fond (bleue)
}

int main()
{
    const int width = 800;                             // Largeur de l'image
    const int height = 600;                            // Hauteur de l'image
    const int channels = 3;                            // Nombre de canaux de couleur (RGB)
    const int samples_per_pixel = 4;                   // Nombre d'échantillons par pixel pour antialiasing
    float aspect_ratio = (float)width / (float)height; // Calcul du ratio largeur/hauteur

    unsigned char *image = new unsigned char[width * height * channels]; // Allocation de mémoire pour l'image

    Scene scene;                                                // Création de la scène
    scene.addPlane(Plane(Vector3(0, -1, 0), Vector3(0, 1, 0))); // Ajout d'un plan représentant le sol

    Vector3 light_position = Vector3(5, 5, 0); // Position de la lumière devant la sphère

    float sphere_x = 0.0f;
    float sphere_y = 0.0f;
    float sphere_z = -5.0f;

    scene.addSphere(Sphere(Vector3(sphere_x, sphere_y, sphere_z), 1)); // Ajout d'une sphère rouge dans la scène

    // Parcours de chaque pixel de l'image
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            Vector3 color(0, 0, 0); // Initialisation de la couleur du pixel

            // Calcul de la couleur du pixel en utilisant des échantillons pour lisser les bords
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                float u = (i + (float)rand() / RAND_MAX) / (float)width;  // Calcul de la coordonnée horizontale normalisée
                float v = (j + (float)rand() / RAND_MAX) / (float)height; // Calcul de la coordonnée verticale normalisée
                float x = (2 * u - 1) * aspect_ratio;                     // Ajustement de la position en fonction du ratio
                float y = (1 - 2 * v);

                Ray ray(Vector3(0, 0, 0), Vector3(x, y, -1)); // Création d'un rayon partant de la caméra

                color = color + calculateColor(ray, scene, light_position); // Accumulation de la couleur calculée
            }

            color = color * (1.0f / samples_per_pixel);                                       // Moyenne des couleurs pour antialiasing
            image[(j * width + i) * channels + 0] = (unsigned char)std::min(255.0f, color.x); // Couleur rouge
            image[(j * width + i) * channels + 1] = (unsigned char)std::min(255.0f, color.y); // Couleur verte
            image[(j * width + i) * channels + 2] = (unsigned char)std::min(255.0f, color.z); // Couleur bleue
        }
    }

    const char *filename = "output.png";
    if (!stbi_write_png(filename, width, height, channels, image, width * channels)) // Sauvegarde de l'image au format PNG
    {
        printf("Erreur lors de l'écriture de l'image : %s\n", filename);
        delete[] image; // Libération de la mémoire en cas d'erreur
        return 1;
    }

    printf("Image %s générée.\n", filename);

    delete[] image; // Libération de la mémoire de l'image

    return 0; // Fin du programme
}
