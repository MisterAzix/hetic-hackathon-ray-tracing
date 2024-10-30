#include <iostream>
#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Ray.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include "src/Square.h"
#include "src/Triangle.h"
#include "src/Camera.h"
#include "src/Light.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr auto OUTPUT_FILENAME = "output.png";
constexpr float FOV = 30.0f;

Color computeLighting(const Scene& scene, const Vector3& point, const Vector3& normal, const Color& objectColor) {
    Color finalColor(0, 0, 0);
    for (const auto& light : scene.lights) {
        Vector3 lightDir = (light.position - point).normalize();
        float diff = std::max(normal.dot(lightDir), 0.0f);
        finalColor = finalColor + objectColor * light.color * diff * light.intensity;
    }
    return finalColor;
}

int main() {
    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

    Camera camera(FOV, aspectRatio, Vector3(0, 0, 20), Vector3(0, 0, -1), Vector3(0, 1, 0));
    Scene scene;
    scene.addObject(new Sphere(Vector3(4, 0, -5), 1, Color(0.0f, 1.0f, 1.0f)));
    scene.addObject(new Sphere(Vector3(0, 0, -5), 1, Color(1.0f, 1.0f, 0.0f)));
    scene.addObject(new Plane(Vector3(0, -1, 0), Vector3(0, 1, 0), Color(0.0f, 0.0f, 1.0f)));
    scene.addObject(new Square(Vector3(2, 1, -4), 2.0f, Color(0.0f, 1.0f, 0.0f)));
    scene.addObject(new Triangle(Vector3(-3, 1, -4), Vector3(-1, 1, -4), Vector3(-2, 2, -4), Color(1.0f, 0.5f, 0.0f)));

    scene.addLight(Light(Vector3(10, 10, 10), Color(1.0f, 1.0f, 1.0f), 2.0f));

    for (int j = 0; j < WINDOW_HEIGHT; ++j) {
        for (int i = 0; i < WINDOW_WIDTH; ++i) {
            Ray ray = camera.generateRay(i, j, WINDOW_WIDTH, WINDOW_HEIGHT);

            Color pixelColor(0, 0, 0);
            float traceDistance;
            int objectId;
            bool isSphere;
            if (scene.trace(ray, traceDistance, objectId, isSphere)) {
                Vector3 hitPoint = ray.origin + ray.direction * traceDistance;
                Vector3 normal = scene.getObjectById(objectId)->getNormal(hitPoint);
                Color objectColor = scene.getObjectById(objectId)->getColor();
                pixelColor = computeLighting(scene, hitPoint, normal, objectColor);
            }

            image.SetPixel(i, j, pixelColor);
        }
    }

    image.WriteFile(OUTPUT_FILENAME);
    std::cout << "Image saved to " << OUTPUT_FILENAME << std::endl;

    return 0;
}