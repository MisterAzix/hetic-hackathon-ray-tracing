#include "Scene.h"
#include "Sphere.h"

// Constructeur pour initialiser la lumière ambiante
Scene::Scene() : ambientLight(Color(0.1f, 0.1f, 0.1f)) {} // Valeur par défaut

void Scene::addObject(Object *object) {
    objects.push_back(object);
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

bool Scene::trace(const Ray &ray, float &trace_distance, int &object_id) const {
    trace_distance = 1e20;
    bool hit = false;

    for (int i = 0; i < objects.size(); ++i) {
        float distance;
        if (objects[i]->intersect(ray, distance) && distance < trace_distance) {
            trace_distance = distance;
            object_id = i;
            hit = true;
        }
    }

    return hit;
}

Object* Scene::getObjectById(int index) const {
    if (index < 0 || index >= objects.size()) {
        return nullptr;
    }
    return objects[index];
}
