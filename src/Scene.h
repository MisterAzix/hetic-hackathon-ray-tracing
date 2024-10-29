#pragma once
#include <vector>
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"

class Scene
{
public:
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;

    void addSphere(const Sphere &sphere)
    {
        spheres.push_back(sphere);
    }

    void addPlane(const Plane &plane)
    {
        planes.push_back(plane);
    }

    bool trace(const Ray &ray, float &trace_distance, int &object_id, bool &isSphere) const
    {
        trace_distance = 1e20;
        bool hit = false;
        isSphere = false;

        for (int i = 0; i < spheres.size(); ++i)
        {
            float distance;
            if (spheres[i].intersect(ray, distance) && distance < trace_distance)
            {
                trace_distance = distance;
                object_id = i;
                hit = true;
                isSphere = true;
            }
        }

        for (int i = 0; i < planes.size(); ++i)
        {
            float distance;
            if (planes[i].intersect(ray, distance) && distance < trace_distance)
            {
                trace_distance = distance;
                object_id = i;
                hit = true;
                isSphere = false;
            }
        }

        return hit;
    }
};