#pragma once
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"

class Object
{
public:
    virtual bool intersect(const Ray &ray, float &t) const = 0;

    virtual Color getColor() const = 0;

    bool isMetal = false;
    float metalRoughness = 0.1f;

    virtual Color getColorAt(const Vector3 &hit_point) const {
        if (!isMetal) {
            return getColor();
        }

        // Get the base color of the object
        Color baseColor = getColor();
        
        // Get the surface normal at this point
        Vector3 normal = getNormal(hit_point).normalize();
        
        // Create metallic effect:
        // 1. Basic fresnel effect (metal gets brighter at glancing angles)
        float fresnel = std::abs(normal.y);  // Simplification of fresnel
        
        // 2. Add some variation based on surface orientation
        float normalVariation = (normal.y + 1.0f) * 0.5f;
        
        // 3. Combine effects
        float metallic = fresnel * (1.0f - metalRoughness) + 
                        normalVariation * metalRoughness;
        
        // 4. Apply to base color
        return baseColor * (metallic + 0.2f);  // 0.2 is ambient light factor
    }
    virtual Vector3 getNormal(const Vector3 &point) const = 0;
    

    virtual ~Object() = default;

    float reflectivity = 0.0f;
    virtual float getReflectivity() const { return reflectivity; }
};
