#include <cmath>
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