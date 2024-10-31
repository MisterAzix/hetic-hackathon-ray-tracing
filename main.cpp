#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Ray.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include "src/Square.h"
#include "src/Triangle.h"
#include "src/Camera.h"
#include "src/Light.h"
#include "src/Lighting.h"

constexpr int WINDOW_WIDTH = 4096;
constexpr int WINDOW_HEIGHT = 2160;
constexpr auto OUTPUT_FILENAME = "output.png";
constexpr float FOV = 30.0f;

// Global mutex for thread-safe pixel writing
std::mutex imageMutex;

// Thread worker function to render a section of the image
void renderSection(Image& image, const Camera& camera, const Scene& scene, 
                  int startRow, int endRow) {
    // Process each assigned row
    for (int j = startRow; j < endRow; ++j) {
        // Process each pixel in the row
        for (int i = 0; i < WINDOW_WIDTH; ++i) {
            // Generate ray for this pixel
            Ray ray = camera.generateRay(i, j, WINDOW_WIDTH, WINDOW_HEIGHT);

            // Variables to store intersection results
            float traceDistance;
            int objectId;

            // Check if ray hits any object
            if (scene.trace(ray, traceDistance, objectId)) {
                // Get the object that was hit
                Object* object = scene.getObjectById(objectId);

                if (object) {
                    // Calculate intersection point
                    Vector3 hit_point = ray.origin + ray.direction * traceDistance;
                    
                    // Get surface normal at intersection
                    Vector3 normal = object->getNormal(hit_point);
                    
                    // Get object color at intersection point
                    Color objectColor = object->getColorAt(hit_point);
                    
                    // Calculate final pixel color with lighting
                    Color pixelColor = computeLighting(scene, hit_point, normal, ray, objectColor);

                    // Thread-safe pixel writing
                    {
                        std::lock_guard<std::mutex> lock(imageMutex);
                        image.SetPixel(i, j, pixelColor);
                    }
                }
            } else {
                // No intersection - set background color (black)
                std::lock_guard<std::mutex> lock(imageMutex);
                image.SetPixel(i, j, Color(0, 0, 0));
            }
        }
    }
}

int main() {
    // Initialize image and calculate aspect ratio
    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;

    // Set up camera
    Camera camera(FOV, aspectRatio, Vector3(0, 0, 20), Vector3(0, 0, -1), Vector3(0, 1, 0));
    Scene scene;

    // Add light to the scene
    scene.addLight(Light(Vector3(10, 10, 10), Color(1.0f, 1.0f, 1.0f), 2.0f));

    // Add objects to the scene
    scene.addObject(new Sphere(Vector3(4, 0, -5), 1, Color(0.0f, 1.0f, 1.0f), 0.4f));
    scene.addObject(new Sphere(Vector3(0, 0, -5), 1, Color(1.0f, 1.0f, 0.0f), 0.4f));
    scene.addObject(new Sphere(Vector3(-4,0,-5),1,Color(0.0f, 1.0f, 1.0f),0.5f));
    scene.addObject(new Plane(Vector3(0, -1, 0), Vector3(0, 1, 0), Color(0.0f, 0.0f, 1.0f), 0.6f));
    scene.addObject(new Square(Vector3(2, 1, -4), 2.0f, Color(0.0f, 1.0f, 0.0f), 0.3f));
    scene.addObject(new Triangle(Vector3(-3, 1, -4), Vector3(-1, 1, -4), Vector3(-2, 2, -4), 
                               Color(1.0f, 0.5f, 0.0f), 0.3f));

    // Get number of available threads
    const int threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Calculate rows per thread
    const int rowsPerThread = WINDOW_HEIGHT / threadCount;

    auto start = std::chrono::high_resolution_clock::now();


    // Create and start threads
    for (int i = 0; i < threadCount; ++i) {
        int startRow = i * rowsPerThread;
        // Handle last thread to ensure all rows are covered
        int endRow = (i == threadCount - 1) ? WINDOW_HEIGHT : (i + 1) * rowsPerThread;
        
        threads.emplace_back(renderSection, 
                           std::ref(image), 
                           std::ref(camera), 
                           std::ref(scene), 
                           startRow, 
                           endRow);
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time taken: " << diff.count() << " seconds\n";

    // Save the rendered image
    image.WriteFile(OUTPUT_FILENAME);
    std::cout << "Image saved to " << OUTPUT_FILENAME << std::endl;
    std::cout << "Rendered using " << threadCount << " threads" << std::endl;

    return 0;
}