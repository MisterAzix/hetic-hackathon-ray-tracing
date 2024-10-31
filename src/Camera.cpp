#include <cmath>
#include <thread>
#include <vector>
#include "Camera.h"
#include "Ray.h"
#include "Vector3.h"

Camera::Camera(float fov, float aspectRatio, const Vector3 &position, const Vector3 &direction, const Vector3 &up)
: fov(fov), aspectRatio(aspectRatio), position(position), direction(direction.normalize()) {
    this->right = direction.cross(up).normalize();
    this->up = this->right.cross(direction).normalize();
}

Ray Camera::generateRay(int i, int j, int width, int height) const {
    float scale = tan(fov * 0.5 * M_PI / 180.0);
    float u = (2 * (i + 0.5f) / width - 1) * scale * aspectRatio;
    float v = (1 - 2 * (j + 0.5f) / height) * scale;

    Vector3 rayDirection = (direction + u * right + v * up).normalize();
    return Ray(position, rayDirection);
}

void Camera::render(const Scene &scene, Image &image) const {
    int width = image.getWidth();
    int height = image.getHeight();
    int numThreads = std::thread::hardware_concurrency();
    int bandHeight = height / numThreads;

    auto renderBand = [&](int startY, int endY) {
        for (int j = startY; j < endY; ++j) {
            for (int i = 0; i < width; ++i) {
                Ray ray = generateRay(i, j, width, height);

                float traceDistance;
                int objectId;

                if (scene.trace(ray, traceDistance, objectId)) {
                    Object *object = scene.getObjectById(objectId);

                    if (object) {
                        Vector3 hit_point = ray.origin + ray.direction * traceDistance;
                        Vector3 normal = object->getNormal(hit_point);

                        Color objectColor = object->getColorAt(hit_point);

                        Color pixelColor = computeLighting(scene, hit_point, normal, ray, objectColor);

                        image.SetPixel(i, j, pixelColor);
                    }
                } else {
                    image.SetPixel(i, j, Color(0, 0, 0));
                }
            }
        }
    };

    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t) {
        int startY = t * bandHeight;
        int endY = (t == numThreads - 1) ? height : startY + bandHeight;
        threads.emplace_back(renderBand, startY, endY);
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

Color Camera::computeLighting(const Scene &scene, const Vector3 &point, const Vector3 &normal, const Ray &incomingRay, const Color &objectColor, int depth) const {
    Color finalColor(0, 0, 0);
    for (const auto &light : scene.lights) {
        Vector3 lightDir = (light.position - point).normalize();
        float diff = std::max(normal.dot(lightDir), 0.0f);
        finalColor = finalColor + objectColor * light.color * diff * light.intensity;
    }
    if (depth > 0) {
        Vector3 reflectionDir = incomingRay.direction - normal * 2.0f * normal.dot(incomingRay.direction);
        Ray reflectionRay(point + reflectionDir * 1e-4f, reflectionDir);
        float traceDistance;
        int reflectedObjectId;

        if (scene.trace(reflectionRay, traceDistance, reflectedObjectId)) {
            Object *reflectedObject = scene.getObjectById(reflectedObjectId);
            if (reflectedObject) {
                Vector3 reflectedPoint = reflectionRay.origin + reflectionRay.direction * traceDistance;
                Vector3 reflectedNormal = reflectedObject->getNormal(reflectedPoint);
                Color reflectedColor = reflectedObject->getColorAt(reflectedPoint);

                Color reflectionColor = computeLighting(scene, reflectedPoint, reflectedNormal, reflectionRay, reflectedColor, depth - 1);
                finalColor = finalColor + reflectionColor * reflectedObject->getReflectivity();
            }
        }
    }
    return finalColor;
}