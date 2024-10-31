#include <iostream>
#include <chrono>
#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include "src/Square.h"
#include "src/Triangle.h"
#include "src/Camera.h"
#include "src/Light.h"

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr auto OUTPUT_FILENAME = "output.png";
constexpr float FOV = 30.0f;

void printSplashScreen() {
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

int main() {
    printSplashScreen();

    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

    Camera camera(FOV, aspectRatio, Vector3(0, 2, 20), Vector3(0, 0, -1), Vector3(0, 1, 0));
    Scene scene;

    scene.addLight(Light(Vector3(3, 2, -3), Color(1.0f, 1.0f, 1.0f), 1.0f));

    scene.addObject(new Sphere(Vector3(4, 0, -5), 1, Color(0.0f, 1.0f, 1.0f), 0.4f));
    scene.addObject(new Sphere(Vector3(0, 0, -5), 1, Color(1.0f, 1.0f, 0.0f), 0.4f));
    scene.addObject(new Plane(Vector3(0, -1, 0), Vector3(0, 1, 0), Color(0.0f, 0.0f, 1.0f), 0.6f));
    scene.addObject(new Square(Vector3(2, 1, -4), 2.0f, Color(0.0f, 1.0f, 0.0f), 0.3f));
    scene.addObject(new Triangle(Vector3(-3, 1, -4), Vector3(-1, 1, -4), Vector3(-2, 2, -4), Color(1.0f, 0.5f, 0.0f), 0.3f));

    std::cout << "Starting image generation..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    camera.render(scene, image);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    image.WriteFile(OUTPUT_FILENAME);

    std::cout << "Image saved to " << OUTPUT_FILENAME << " (" << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << ") in " << elapsed.count() << " secondsa" << std::endl;
    return 0;
}