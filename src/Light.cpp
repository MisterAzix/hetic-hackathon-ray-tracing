#include "Light.h"
#include "Vector3.h"
#include "Color.h"

Light::Light(const Vector3& position, const Color& color, float intensity)
    : position(position), color(color), intensity(intensity) {}