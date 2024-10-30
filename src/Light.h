#pragma once
#include "Vector3.h"
#include "Color.h"

class Light {
public:
    Vector3 position;
    Color color;
    float intensity;

    Light(const Vector3& position, const Color& color, float intensity);
};