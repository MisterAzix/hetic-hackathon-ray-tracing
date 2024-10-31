#pragma once
#include "Ray.h"
#include "Vector3.h"
#include "Scene.h"
#include "Image.h"
#include "Color.h"

class Camera {
public:
    Camera(float fov, float aspectRatio, const Vector3 &position, const Vector3 &direction, const Vector3 &up);
    Ray generateRay(int i, int j, int width, int height) const;
    void render(const Scene &scene, Image &image) const;

private:
    float fov;
    float aspectRatio;
    Vector3 position;
    Vector3 direction;
    Vector3 right;
    Vector3 up;

    Color computeLighting(const Scene &scene, const Vector3 &point, const Vector3 &normal, const Ray &incomingRay, const Color &objectColor, int depth = 3) const;
};