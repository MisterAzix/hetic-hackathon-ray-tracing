#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include "src/Camera.h"
#include "src/Light.h"

constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
constexpr float FOV = 30.0f;
constexpr int SPHERE_COUNT = 50;
constexpr float POSITION_DISTRIBUTION_MIN = -10.0f;
constexpr float POSITION_DISTRIBUTION_MAX = 10.0f;
constexpr float COLOR_DISTRIBUTION_MIN = 0.0f;
constexpr float COLOR_DISTRIBUTION_MAX = 1.0f;

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

unsigned getSeedFromUser() {
    unsigned seed;
    while (true) {
        std::cout << "Enter a seed (or press Enter to use a random seed): ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            seed = std::chrono::system_clock::now().time_since_epoch().count();
            break;
        }

        try {
            seed = std::stoul(input);
            break;
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid input. Please enter a valid number." << std::endl;
        } catch (const std::out_of_range&) {
            std::cerr << "Input out of range. Please enter a smaller number." << std::endl;
        }
    }
    return seed;
}

void generateScene(Scene& scene, std::default_random_engine& generator) {
    std::uniform_real_distribution<float> position_distribution(POSITION_DISTRIBUTION_MIN, POSITION_DISTRIBUTION_MAX);
    std::uniform_real_distribution<float> color_distribution(COLOR_DISTRIBUTION_MIN, COLOR_DISTRIBUTION_MAX);

    for (int i = 0; i < SPHERE_COUNT; ++i) {
        Vector3 position(position_distribution(generator), position_distribution(generator), position_distribution(generator));
        Color color(color_distribution(generator), color_distribution(generator), color_distribution(generator));
        scene.addObject(new Sphere(position, 1.0f, color, 0.4f));
    }
}

int main() {
    printSplashScreen();

    unsigned seed = getSeedFromUser();
    std::default_random_engine generator(seed);

    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

    Camera camera(FOV, aspectRatio, Vector3(0, 2, 20), Vector3(0, 0, -1), Vector3(0, 1, 0));
    Scene scene;

    scene.addLight(Light(Vector3(3, 2, -3), Color(1.0f, 1.0f, 1.0f), 1.0f));
    generateScene(scene, generator);

    std::cout << "Starting image generation..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    camera.render(scene, image);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::string outputFilename = "output_" + std::to_string(seed) + ".png";
    image.WriteFile(outputFilename.c_str());

    std::cout << "Image saved to " << outputFilename << " (" << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << ") in " << elapsed.count() << " seconds" << std::endl;
    return 0;
}