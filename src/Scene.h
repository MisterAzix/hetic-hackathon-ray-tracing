#pragma once
#include <vector>
#include "Object.h"
#include "Ray.h"
#include "Light.h"

class Scene {
public:
    std::vector<Object*> objects;
    std::vector<Light> lights;

    void addObject(Object *object);
    void addLight(const Light& light);
    bool trace(const Ray &ray, float &trace_distance, int &object_id, bool &isSphere) const;
    Object* getObjectById(int index) const;
};