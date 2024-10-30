#pragma once
#include <vector>
#include "Object.h"
#include "Ray.h"

class Scene
{
public:
    std::vector<Object*> objects;

    void addObject(Object *object);
    bool trace(const Ray &ray, float &trace_distance, int &object_id, bool &isSphere) const;
    
    Object* getObject(int index) const;
};