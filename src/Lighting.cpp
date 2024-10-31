#include "Lighting.h"

Color computeLighting(const Scene &scene, const Vector3 &point, const Vector3 &normal, const Ray &incomingRay, const Color &objectColor, int depth) {
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
