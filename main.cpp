#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include "src/Camera.h"
#include "src/Light.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

constexpr int WINDOW_WIDTH = 4096;
constexpr int WINDOW_HEIGHT = 2160;
constexpr auto OUTPUT_FILENAME = "output.png";
constexpr float FOV = 45.0f;
constexpr int NUM_RINGS = 5;
constexpr float RING_WIDTH = 5.0f;

void printSplashScreen()
{
    std::cout << R"(
===================================================================================================

    |   |  ____| __ __| _ _|   ___|       _ \              __ __|   _ \
    |   |  __|      |     |   |          |   |   _` |  |   |  |    |   |   _` |   __|   _ \   __|
    ___ |  |        |     |   |          __ <   (   |  |   |  |    __ <   (   |  (      __/  |
   _|  _| _____|   _|   ___| \____|     _| \_\ \__,_| \__, | _|   _| \_\ \__,_| \___| \___| _|
                                                    ____/
===================================================================================================
    )" << std::endl;
}

int main()
{
    printSplashScreen();
    std::cout << "Starting image generation..." << std::endl;

    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

    Camera camera(FOV, aspectRatio, Vector3(0, 20, 45), Vector3(0, -0.5, -1), Vector3(0, 1, 0));
    Scene scene;

    srand(static_cast<unsigned int>(time(0)));

    scene.addLight(Light(Vector3(0, 5, 0), Color(1.0f, 0.9f, 0.6f), 1.0f));
    scene.addLight(Light(Vector3(3, 2, -3), Color(1.0f, 1.0f, 0.0f), 1.0f));
    scene.addLight(Light(Vector3(10, 10, 10), Color(1.0f, 0.0f, 1.0f), 0.3f));
    scene.addLight(Light(Vector3(-10, 10, 10), Color(0.0f, 0.0f, 1.0f), 0.3f));

    Vector3 sunPosition(0, 0, 0);
    Sphere *sun = new Sphere(sunPosition, 2.5, Color(1.0f, 0.7f, 0.1f), 0.8f);
    sun->isMetal = true;
    scene.addObject(sun);
    sun->metalRoughness = 0.3f;

    float planetHeight = 0.0f;

    const PlanetTextures::PlanetType planetTypes[] = {
        PlanetTextures::MARS,
        PlanetTextures::EARTH,
        PlanetTextures::MOON,
        PlanetTextures::JUPITER,
        PlanetTextures::SATURN};

    for (int ring = 1; ring <= NUM_RINGS; ++ring)
    {
        float radius = ring * RING_WIDTH;
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        float planetSize = 0.5f + 0.1f * ring;

        Sphere *planet = new Sphere(Vector3(x, planetHeight, z),
                                    planetSize,
                                    Color(1.0f, 1.0f, 1.0f),
                                    0.4f);

        planet->planetType = planetTypes[(ring - 1) % 5];
        planet->isMetal = true;
        planet->metalRoughness = 0.7f;

        scene.addObject(planet);
    }

    scene.addObject(new Plane(Vector3(0, -1, 0), Vector3(0, 1, 0), Color(0.0f, 0.0f, 0.0f), 0.0f));

    auto start = std::chrono::high_resolution_clock::now();
    camera.render(scene, image);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    image.WriteFile(OUTPUT_FILENAME);
    std::cout << "Image saved to " << OUTPUT_FILENAME << " (" << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << ") in " << elapsed.count() << " seconds" << std::endl;
    return 0;
}
