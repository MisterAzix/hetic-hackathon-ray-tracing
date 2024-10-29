#include "src/Color.h"
#include "src/Image.h"
#include "src/Vector3.h"
#include "src/Ray.h"
#include "src/Sphere.h"
#include "src/Plane.h"
#include "src/Scene.h"
#include <iostream>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr auto OUTPUT_FILENAME = "output.png";

Ray generateRay(int i, int j, int width, int height, float fov, float aspect_ratio, Vector3 camera_position, Vector3 look_at)
{
    float scale = tan((fov * 0.5) * (M_PI / 180.0));
    float u = (i + 0.5f) / width;
    float v = (j + 0.5f) / height;
    float x = (2 * u - 1) * aspect_ratio * scale;
    float y = (1 - 2 * v) * scale;

    Vector3 forward = (look_at - camera_position).normalize();
    Vector3 right = Vector3(0, 1, 0).cross(forward).normalize();
    Vector3 up = forward.cross(right);

    Vector3 direction = (forward + (x * right) + (y * up)).normalize();
    return Ray(camera_position, direction);
}

int main() {
    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);
    float aspect_ratio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);

    Scene scene;
    scene.addObject(new Sphere(Vector3(7, 0, -5), 1));
    scene.addObject(new Sphere(Vector3(-12, 0, -5), 1));
    scene.addObject(new Sphere(Vector3(0, 0, -5), 1));
    scene.addObject(new Plane(Vector3(0, -1, 0), Vector3(0, 1, 0)));

    Vector3 camera_position = Vector3(0, 1, 20);
    Vector3 look_at = Vector3(0, 0, -1);

    for (int j = 0; j < WINDOW_HEIGHT; ++j) {
        for (int i = 0; i < WINDOW_WIDTH; ++i) {
            float u = static_cast<float>(i) / static_cast<float>(WINDOW_WIDTH);
            float v = static_cast<float>(j) / static_cast<float>(WINDOW_HEIGHT);
            float x = (2 * u - 1) * aspect_ratio;
            float y = (1 - 2 * v);

            Ray ray = generateRay(i, j, WINDOW_WIDTH, WINDOW_HEIGHT, 45, aspect_ratio, camera_position, look_at);

            Color pixelColor(0, 0, 1);
            float trace_distance;
            int object_id;
            bool isSphere;
            if (scene.trace(ray, trace_distance, object_id, isSphere)) {
                if (isSphere) {
                    pixelColor = Color(1.0f, 0.0f, 0.0f);
                } else {
                    pixelColor = Color(0.0f, 1.0f, 0.0f);
                }
            }

            image.SetPixel(i, j, pixelColor);
        }
    }

    image.WriteFile(OUTPUT_FILENAME);
    std::cout << "Image saved to " << OUTPUT_FILENAME << std::endl;

    return 0;
}