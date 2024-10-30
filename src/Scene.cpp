#include "Scene.h"
#include "Sphere.h"

void Scene::addObject(Object *object)
{
    objects.push_back(object);
}

bool Scene::trace(const Ray &ray, float &trace_distance, int &object_id, bool &isSphere) const
{
    trace_distance = 1e20;
    bool hit = false;

    for (int i = 0; i < objects.size(); ++i)
    {
        float distance;
        if (objects[i]->intersect(ray, distance) && distance < trace_distance)
        {
            trace_distance = distance;
            object_id = i;
            hit = true;
            isSphere = dynamic_cast<Sphere*>(objects[i]) != nullptr;
        }
    }

    return hit;
}
Object* Scene::getObjectById(int index) const
{
    if (index < 0 || index >= objects.size())
    {
        return nullptr;
    }
    return objects[index];
}