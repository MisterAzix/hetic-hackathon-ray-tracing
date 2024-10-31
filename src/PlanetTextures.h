#pragma once
#include "Color.h"
#include "Vector3.h"

class PlanetTextures {
public:
    enum PlanetType {
        NONE,
        EARTH,
        MOON,
        MARS,
        JUPITER,
        SATURN
    };

    static Color getEarthColor(const Vector3 &point, const Vector3 &normal) {
    Color oceanColor(0.1f, 0.3f, 0.7f);
    Color landColor(0.3f, 0.5f, 0.2f);
    Color iceColor(0.9f, 0.9f, 0.95f);

    // Use more continuous functions instead of hard blocks
    float latitude = normal.y;
    float longitude = atan2(normal.z, normal.x);
    
    // Smoother continent pattern
    float continentPattern = sin(latitude * 4) * cos(longitude * 4) + 
                           sin(latitude * 8) * cos(longitude * 8) * 0.5f;

    // Smoother transitions
    if (abs(latitude) > 0.8f) {
        // Pole regions
        float poleBlend = (abs(latitude) - 0.8f) * 5.0f;  // Smooth transition
        return iceColor * poleBlend + oceanColor * (1 - poleBlend);
    }

    if (continentPattern > 0) {
        float blend = (continentPattern + 1) * 0.5f;
        return landColor * blend + oceanColor * (1 - blend);
    }
    return oceanColor;
}

    static Color getMoonColor(const Vector3 &point, const Vector3 &normal) {
        Color brightColor(0.8f, 0.8f, 0.75f);
        Color darkColor(0.4f, 0.4f, 0.35f);

        // Create crater-like pattern
        float pattern = sin(normal.x * 10) * sin(normal.z * 10);
        return brightColor * pattern + darkColor * (1 - pattern);
    }

    static Color getMarsColor(const Vector3 &point, const Vector3 &normal) {
        Color rustColor(0.7f, 0.3f, 0.2f);
        Color darkColor(0.4f, 0.2f, 0.1f);

        // Create Mars-like patterns
        float pattern = (sin(normal.y * 15) + 1) * 0.5f;
        return rustColor * pattern + darkColor * (1 - pattern);
    }
    static Color getJupiterColor(const Vector3 &point, const Vector3 &normal) {
        // Jupiter's colors
        Color bandLight(0.9f, 0.8f, 0.6f);    // Light bands
        Color bandDark(0.7f, 0.5f, 0.2f);     // Dark bands
        Color redSpot(0.8f, 0.3f, 0.2f);      // Great Red Spot

        // Get latitude for banding
        float latitude = normal.y;
        float longitude = atan2(normal.z, normal.x);

        // Create Jupiter's distinctive bands
        float bands = sin(latitude * 15.0f);  // More frequent bands
        
        // Add turbulence to bands
        float turbulence = sin(latitude * 30.0f + longitude * 4.0f) * 0.2f;
        bands += turbulence;

        // Great Red Spot
        float spot = exp(-(pow(longitude - 0.5f, 2) + pow(latitude - 0.2f, 2)) * 10.0f);
        
        // Blend colors
        Color baseColor;
        if(bands > 0) {
            baseColor = bandLight;
        } else {
            baseColor = bandDark;
        }

        // Add the Great Red Spot
        return baseColor * (1.0f - spot) + redSpot * spot;
    }

    static Color getSaturnColor(const Vector3 &point, const Vector3 &normal) {
        // Saturn's colors
        Color bandLight(0.9f, 0.85f, 0.7f);    // Light bands
        Color bandDark(0.8f, 0.7f, 0.5f);      // Dark bands
        
        // Get coordinates
        float latitude = normal.y;
        float longitude = atan2(normal.z, normal.x);

        // Create Saturn's subtle bands
        float bands = sin(latitude * 12.0f);
        
        // Add subtle turbulence
        float turbulence = sin(latitude * 20.0f + longitude * 3.0f) * 0.15f;
        bands += turbulence;

        // Ring shadow effect
        float ringShadow = 1.0f;
        if (abs(latitude) < 0.2f) {  // Shadow zone
            ringShadow = 0.7f + abs(latitude) * 1.5f;  // Gradual shadow
        }

        // Blend colors based on bands
        Color baseColor = bands > 0 ? bandLight : bandDark;
        
        // Apply ring shadow
        return baseColor * ringShadow;
    }
};