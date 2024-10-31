#pragma once
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"
#include "PlanetTextures.h"

class Object
{
public:
    virtual bool intersect(const Ray &ray, float &t) const = 0;

    virtual Color getColor() const = 0;

    bool isMetal = false;
    float metalRoughness = 0.1f;
    PlanetTextures::PlanetType planetType = PlanetTextures::NONE;
    virtual Color getColorAt(const Vector3 &hit_point) const
    {

        if (planetType != PlanetTextures::NONE)
        {
            Vector3 normal = getNormal(hit_point).normalize();
            switch (planetType)
            {
            case PlanetTextures::EARTH:
                return PlanetTextures::getEarthColor(hit_point, normal);
            case PlanetTextures::MOON:
                return PlanetTextures::getMoonColor(hit_point, normal);
            case PlanetTextures::MARS:
                return PlanetTextures::getMarsColor(hit_point, normal);
            case PlanetTextures::JUPITER:
                return PlanetTextures::getJupiterColor(hit_point, normal);
            case PlanetTextures::SATURN:
                return PlanetTextures::getSaturnColor(hit_point, normal);
            default:
                return getColor();
            }
        }

        if (isMetal)
        {
            Color baseColor = getColor();
            Vector3 normal = getNormal(hit_point).normalize();

            float fresnel = std::abs(normal.y);
            float normalVariation = (normal.y + 1.0f) * 0.5f;
            float metallic = fresnel * (1.0f - metalRoughness) +
                             normalVariation * metalRoughness;

            return baseColor * (metallic + 0.2f);
        }

        return getColor();
    }
    virtual Vector3 getNormal(const Vector3 &point) const = 0;

    virtual ~Object() = default;

    float reflectivity = 0.0f;
    virtual float getReflectivity() const { return reflectivity; }
};
