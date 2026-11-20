
#include "io.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstddef>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

Image load_image(const std::string& filepath) {
    int width;
    int height;
    int channels;

    unsigned char* raw_data = stbi_load(
        filepath.c_str(),
        &width,
        &height,
        &channels,
        3
    );

    if (raw_data == nullptr) {
        const char* reason = stbi_failure_reason();

        throw std::runtime_error(
            "Failed to load image '" + filepath + "': " +
            (reason ? reason : "unknown error")
        );
    }

    std::unique_ptr<unsigned char, decltype(&stbi_image_free)>
        data(raw_data, stbi_image_free);

    const std::size_t image_width =
        static_cast<std::size_t>(width);

    const std::size_t image_height =
        static_cast<std::size_t>(height);

    Image image(image_width, image_height);

    // Copy the RGB data into Image representation
    for (std::size_t y = 0; y < image_height; y++) {
        for (std::size_t x = 0; x < image_width; x++) {
            const std::size_t index =
                (y * image_width + x) * 3;

            image.at(x, y) = Pixel{
                data.get()[index],
                data.get()[index + 1],
                data.get()[index + 2]
            };
        }
    }

    return image;
}

void save_image(
    const Image& image,
    const std::string& filepath
) {
    const std::size_t width = image.width();
    const std::size_t height = image.height();

    const std::size_t max_int =
        static_cast<std::size_t>(
            std::numeric_limits<int>::max()
        );

    // Check that dimensions and buffer size won't overflow
    if (width > max_int / 3 ||
        width > std::numeric_limits<std::size_t>::max()
                    / height / 3) {
        throw std::length_error(
            "Image dimensions are too large to save"
        );
    }

    // Convert Pixel objects into a contiguous RGB byte buffer
    std::vector<unsigned char> data;
    data.reserve(width * height * 3);

    for (std::size_t y = 0; y < height; y++) {
        for (std::size_t x = 0; x < width; x++) {
            const Pixel& pixel = image.at(x, y);

            data.push_back(pixel.r);
            data.push_back(pixel.g);
            data.push_back(pixel.b);
        }
    }

    const int result = stbi_write_png(
        filepath.c_str(),
        static_cast<int>(width),
        static_cast<int>(height),
        3,                              // RGB channels
        data.data(),
        static_cast<int>(width * 3)    // Bytes per row
    );

    if (result == 0) {
        throw std::runtime_error(
            "Failed to save image: " + filepath
        );
    }
}
