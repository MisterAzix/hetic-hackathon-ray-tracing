#include <iostream>
#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Ray.h"
#include "src/Sphere.h"
#include "src/Triangle.h"
#include "src/Square.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include "src/Camera.h"
#include "src/Light.h"
#include <algorithm>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr auto OUTPUT_FILENAME = "output.png";
constexpr float FOV = 30.0f;

bool isInShadow(const Vector3 &point, const Scene &scene, const Vector3 &lightPosition)
{
    Vector3 lightDir = (lightPosition - point).normalize();
    Ray shadowRay(point + lightDir * 0.001f, lightDir);
    float t;
    int id;
    return scene.trace(shadowRay, t, id) && t < (lightPosition - point).length();
}

Color computeLighting(const Scene &scene, const Vector3 &point, const Vector3 &normal, const Color &objectColor, const Ray &viewRay)
{
    Color finalColor(0, 0, 0);
    for (const auto &light : scene.lights)
    {
        Vector3 lightDir = (light.position - point).normalize();

        bool shadow = isInShadow(point, scene, light.position);

        float diff = std::max(normal.dot(lightDir), 0.0f) * (shadow ? 0.3f : 1.0f);
        Color diffuse = objectColor * light.color * diff * light.intensity;

        Vector3 viewDir = -viewRay.direction.normalize();
        Vector3 halfDir = (lightDir + viewDir).normalize();
        float spec = std::pow(std::max(0.0f, normal.dot(halfDir)), 32) * (shadow ? 0.0f : 1.0f);
        Color specular = Color(255, 255, 255) * light.color * spec;

        finalColor = finalColor + diffuse + specular;
    }
    return finalColor;
}

int main()
{
    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

    Camera camera(FOV, aspectRatio, Vector3(0, 2, 20), Vector3(0, 0, -1), Vector3(0, 1, 0));
    Scene scene;

    scene.addObject(new Sphere(Vector3(-2, 2, -2), 1, Color(0.0f, 1.0f, 1.0f)));
    scene.addObject(new Sphere(Vector3(2, 4, -5), 1, Color(0.0f, 1.0f, 1.0f)));
    scene.addObject(new Sphere(Vector3(0, 0, -5), 1, Color(1.0f, 1.0f, 0.0f)));
    scene.addObject(new Plane(Vector3(0, -1, 0), Vector3(0, 1, 0), Color(0.0f, 0.0f, 1.0f)));
    // scene.addObject(new Square(Vector3(2, 1, -4), 2.0f, Color(0.0f, 1.0f, 0.0f)));
    // scene.addObject(new Triangle(Vector3(-3, 1, -4), Vector3(-1, 1, -4), Vector3(-2, 2, -4), Color(1.0f, 0.5f, 0.0f)));

    scene.addLight(Light(Vector3(10, 10, 10), Color(1.0f, 1.0f, 1.0f), 2.0f));

    for (int j = 0; j < WINDOW_HEIGHT; ++j)
    {
        for (int i = 0; i < WINDOW_WIDTH; ++i)
        {
            Ray ray = camera.generateRay(i, j, WINDOW_WIDTH, WINDOW_HEIGHT);

            float traceDistance;
            int objectId;

            if (scene.trace(ray, traceDistance, objectId))
            {
                Object *object = scene.getObjectById(objectId);

                if (object)
                {
                    Vector3 hit_point = ray.origin + ray.direction * traceDistance;
                    Vector3 normal = object->getNormal(hit_point);
                    Color objectColor = object->getColorAt(hit_point);

                    Color pixelColor = computeLighting(scene, hit_point, normal, objectColor, ray);
                    image.SetPixel(i, j, pixelColor);
                }
            }
            else
            {
                image.SetPixel(i, j, Color(0, 0, 0));
            }
        }
    }

    image.WriteFile(OUTPUT_FILENAME);
    std::cout << "Image saved to " << OUTPUT_FILENAME << std::endl;
    return 0;
}
