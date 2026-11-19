#include <gtest/gtest.h>
#include "image.h"

TEST(ImageTest, InitializesDimensions) {
    Image image(3, 2);

    EXPECT_EQ(image.width(), 3);
    EXPECT_EQ(image.height(), 2);
}

TEST(ImageTest, InitializesPixelsToBlack) {
    Image image(3, 2);

    for (std::size_t y = 0; y < image.height(); y++) {
        for (std::size_t x = 0; x < image.width(); x++) {
            EXPECT_EQ(image.at(x, y).r, 0);
            EXPECT_EQ(image.at(x, y).g, 0);
            EXPECT_EQ(image.at(x, y).b, 0);
        }
    }
}

TEST(ImageTest, CanModifyPixel) {
    Image image(3, 2);

    image.at(1, 0) = Pixel{255, 0, 0};

    EXPECT_EQ(image.at(1, 0).r, 255);
    EXPECT_EQ(image.at(1, 0).g, 0);
    EXPECT_EQ(image.at(1, 0).b, 0);

    // Verify that another pixel remains unchanged
    EXPECT_EQ(image.at(0, 0).r, 0);
}

TEST(ImageTest, ThrowsForInvalidCoordinates) {
    Image image(3, 2);

    EXPECT_THROW(image.at(3, 0), std::out_of_range);
}

TEST(ImageTest, ThrowsForZeroWidth) {
    EXPECT_THROW(Image(0, 2), std::invalid_argument);
}