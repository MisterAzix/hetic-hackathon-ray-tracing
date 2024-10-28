#include "src/Color.h"
#include "src/Image.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr auto OUTPUT_FILENAME = "output.png";

int main() {
    Image image(WINDOW_WIDTH, WINDOW_HEIGHT);

    for (int y = WINDOW_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            const Color color(static_cast<float>(x) / WINDOW_WIDTH, static_cast<float>(y) / WINDOW_HEIGHT, 0.2f);
            image.SetPixel(x, y, color);
        }
    }

    image.WriteFile(OUTPUT_FILENAME);
    std::cout << "Image saved to " << OUTPUT_FILENAME << std::endl;
}