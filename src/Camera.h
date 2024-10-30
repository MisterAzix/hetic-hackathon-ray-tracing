#pragma once
#include "Ray.h"
#include "Vector3.h"

class Camera {
public:
    Camera(float fov, float aspectRatio, const Vector3 &position, const Vector3 &direction, const Vector3 &up);
    Ray generateRay(int i, int j, int width, int height) const;

private:
    float fov;
    float aspectRatio;
    Vector3 position;
    Vector3 direction;
    Vector3 right;
    Vector3 up;
};
