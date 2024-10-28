#include <iostream>
#include "src/Color.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main() {
    std::cout << "P3\n" << WINDOW_WIDTH << " " << WINDOW_HEIGHT << "\n255\n";
    for (int j = WINDOW_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < WINDOW_WIDTH; i++) {
            Color color(static_cast<float>(i) / WINDOW_WIDTH, static_cast<float>(j) / WINDOW_HEIGHT, 0.2f);
            int ir = static_cast<int>(255.99 * color.R());
            int ig = static_cast<int>(255.99 * color.G());
            int ib = static_cast<int>(255.99 * color.B());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}