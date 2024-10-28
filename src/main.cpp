#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include <cstdlib>
#include <algorithm>

float attenuation(float distance, float max_distance)
{
    return std::max(0.0f, 1.0f - (distance / max_distance));
}

bool isInShadow(const Vector3 &point, const Scene &scene, const Vector3 &light_position)
{
    Vector3 light_dir = (light_position - point).normalize();
    Ray shadow_ray(point + light_dir * 0.001f, light_dir);
    float t;
    int id;
    bool isSphere;
    return scene.trace(shadow_ray, t, id, isSphere) && t < (light_position - point).length();
}

Vector3 calculateColor(const Ray &ray, const Scene &scene, const Vector3 &light_position, int depth, float max_distance)
{
    if (depth <= 0)
    {
        return Vector3(0, 0, 255);
    }

    float t;
    int id;
    bool isSphere;
    if (scene.trace(ray, t, id, isSphere))
    {
        Vector3 hit_point = ray.origin + ray.direction * t;
        Vector3 normal = isSphere ? (hit_point - scene.spheres[id].center).normalize() : scene.planes[id].normal;
        Vector3 light_dir = (light_position - hit_point).normalize();

        float diff = std::max(0.0f, normal.dot(light_dir));

        Vector3 view_dir = -ray.direction.normalize();
        Vector3 half_dir = (light_dir + view_dir).normalize();
        float spec = std::pow(std::max(0.0f, normal.dot(half_dir)), 32);

        float distance_to_light = (light_position - hit_point).length();
        float attenuation_factor = attenuation(distance_to_light, max_distance);

        Vector3 object_color = isSphere ? Vector3(255, 0, 0) : scene.getCheckerboardColor(hit_point);

        bool shadow = isInShadow(hit_point, scene, light_position);
        float shadow_factor = shadow ? 0.1f : 1.0f;

        Vector3 reflect_dir = ray.direction - normal * 2.0f * ray.direction.dot(normal);
        Ray reflect_ray(hit_point + reflect_dir * 0.001f, reflect_dir);
        Vector3 reflected_color = calculateColor(reflect_ray, scene, light_position, depth - 1, max_distance);

        float reflection_factor = 0.5f;
        Vector3 final_color;

        if (shadow)
        {
            final_color = object_color * diff * shadow_factor;
        }
        else
        {
            final_color = object_color * (diff + 0.1f * spec) * (1.0f - reflection_factor) + reflected_color * reflection_factor;
        }

        return final_color * attenuation_factor;
    }

    return Vector3(0, 0, 255);
}

int main()
{
    const int width = 800;
    const int height = 600;
    const int channels = 3;
    const int samples_per_pixel = 4;
    const int max_depth = 5;
    float aspect_ratio = (float)width / (float)height;
    float max_distance = 20.0f;

    unsigned char *image = new unsigned char[width * height * channels];

    Scene scene;
    scene.addPlane(Plane(Vector3(0, -1, 0), Vector3(0, 1, 0)));

    Vector3 light_position = Vector3(5, 5, -10);

    float sphere_x = 0.0f;
    float sphere_y = 0.0f;
    float sphere_z = -5.0f;

    scene.addSphere(Sphere(Vector3(sphere_x, sphere_y, sphere_z), 1));

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            Vector3 color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; ++s)
            {
                float u = (i + (float)rand() / RAND_MAX) / (float)width;
                float v = (j + (float)rand() / RAND_MAX) / (float)height;
                float x = (2 * u - 1) * aspect_ratio;
                float y = (1 - 2 * v);

                Ray ray(Vector3(0, 0, 0), Vector3(x, y, -1));

                color = color + calculateColor(ray, scene, light_position, max_depth, max_distance);
            }

            color = color * (1.0f / samples_per_pixel);
            image[(j * width + i) * channels + 0] = (unsigned char)std::min(255.0f, color.x);
            image[(j * width + i) * channels + 1] = (unsigned char)std::min(255.0f, color.y);
            image[(j * width + i) * channels + 2] = (unsigned char)std::min(255.0f, color.z);
        }
    }

    const char *filename = "output.png";
    if (!stbi_write_png(filename, width, height, channels, image, width * channels))
    {
        printf("Erreur lors de l'écriture de l'image : %s\n", filename);
        delete[] image;
        return 1;
    }

    printf("Image %s générée.\n", filename);

    delete[] image;

    return 0;
}
