#include <iostream>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main() {
    std::cout << "P3\n" << WINDOW_WIDTH << " " << WINDOW_HEIGHT << "\n255\n";
    for (int j = WINDOW_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < WINDOW_WIDTH; i++) {
            float r = float(i) / float(WINDOW_WIDTH);
            float g = float(j) / float(WINDOW_HEIGHT);
            float b = 0.2;
            int ir = static_cast<int>(255.99 * r);
            int ig = static_cast<int>(255.99 * g);
            int ib = static_cast<int>(255.99 * b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}