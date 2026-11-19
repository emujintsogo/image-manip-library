#pragma once

#include "pixel.h"

#include <vector>
#include <cstddef>

class Image {
    public:
        Image(std::size_t width, std::size_t height);
        
        Image(std::size_t width, std::size_t height, Pixel fill);

        std::size_t width() const;
        std::size_t height() const;

        bool empty() const;
        
        // Reading pixels
        Pixel& at(std::size_t x, std::size_t y);
        const Pixel& at(std::size_t x, std::size_t y) const;
    
    private:
        std::size_t width_;
        std::size_t height_;
        std::vector<Pixel> pixels_;

};