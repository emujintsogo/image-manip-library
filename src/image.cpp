#include "image.h"
#include "pixel.h"

#include <stdexcept>
#include <vector>

namespace {
    // Private helper for Image constructor
    std::size_t checked_pixel_count(
        std::size_t width,
        std::size_t height
    ) {
        if (width == 0 || height == 0) {
            throw std::invalid_argument("Image dimensions must be positive");
        }

        const auto max_size = std::vector<Pixel>{}.max_size();

        if (width > max_size / height) {
            throw std::length_error("Image dimensions are too large");
        }

        return width * height;
    }
}

Image::Image(std::size_t width, std::size_t height)
    : Image(width, height, Pixel{0, 0, 0}) {}

Image::Image(std::size_t width, std::size_t height, Pixel fill)
    : width_(width),
      height_(height),
      pixels_(checked_pixel_count(width, height), fill) {}

std::size_t Image::width() const {
    return width_;
}

std::size_t Image::height() const {
    return height_;
}

bool Image::empty() const {
    return pixels_.empty();
}

// Pixel access
Pixel& Image::at(std::size_t x, std::size_t y) {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Pixel coordinates out of range");
    }

    return pixels_.at(y * width_ + x);
}

const Pixel& Image::at(
    std::size_t x,
    std::size_t y
) const {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("Pixel coordinates out of range");
    }

    return pixels_.at(y * width_ + x);
}