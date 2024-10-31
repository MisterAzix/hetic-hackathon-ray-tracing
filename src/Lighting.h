#include "Scene.h"
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"

Color computeLighting(const Scene &scene, const Vector3 &point, const Vector3 &normal, const Ray &incomingRay, const Color &objectColor, int depth = 3);
