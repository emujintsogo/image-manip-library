#pragma once

#include "image.h"

#include <string>

Image load_image(const std::string& filepath);

void save_image(
    const Image& image,
    const std::string& filepath
);
