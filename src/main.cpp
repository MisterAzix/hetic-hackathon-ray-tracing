#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include <cstdlib>
#include <algorithm>

int main()
{
    const int width = 800;
    const int height = 600;
    const int channels = 3;
    const int samples_per_pixel = 4;
    float aspect_ratio = (float)width / (float)height;

    unsigned char *image = new unsigned char[width * height * channels];

    Scene scene;
    scene.addSphere(Sphere(Vector3(0, 0, -5), 1));
    scene.addPlane(Plane(Vector3(0, -1, 0), Vector3(0, 1, 0)));

    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            float r = 0, g = 0, b = 0;

            for (int s = 0; s < samples_per_pixel; ++s)
            {
                float u = (i + (float)rand() / RAND_MAX) / (float)width;
                float v = (j + (float)rand() / RAND_MAX) / (float)height;
                float x = (2 * u - 1) * aspect_ratio;
                float y = (1 - 2 * v);

                Ray ray(Vector3(0, 0, 0), Vector3(x, y, -1));

                float t;
                int id;
                bool isSphere;
                if (scene.trace(ray, t, id, isSphere))
                {
                    Vector3 hit_point = ray.origin + ray.direction * t;
                    Vector3 normal = isSphere ? (hit_point - scene.spheres[id].center).normalize() : scene.planes[id].normal;

                    if (isSphere)
                    {
                        r += 255;
                        g += 0;
                        b += 0;
                    }
                    else
                    {
                        r += 0;
                        g += 255;
                        b += 0;
                    }
                }
                else
                {
                    r += 0;
                    g += 0;
                    b += 255;
                }
            }

            image[(j * width + i) * channels + 0] = (unsigned char)(r / samples_per_pixel);
            image[(j * width + i) * channels + 1] = (unsigned char)(g / samples_per_pixel);
            image[(j * width + i) * channels + 2] = (unsigned char)(b / samples_per_pixel);
        }
    }

    stbi_write_png("output.png", width, height, channels, image, width * channels);
    delete[] image;

    return 0;
}
