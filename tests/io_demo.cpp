#include "io.h"

#include <exception>
#include <iostream>

int main() {
    try {
        Image image = load_image("examples/test-image.jpg");

        std::cout << "Image loaded successfully!\n";
        std::cout << "Width: " << image.width() << '\n';
        std::cout << "Height: " << image.height() << '\n';

        // Change the top-left pixel to red
        image.at(0, 0) = Pixel{255, 0, 0};

        save_image(image, "examples/output.jpg");

        std::cout << "Image saved to examples/output.jpg\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
