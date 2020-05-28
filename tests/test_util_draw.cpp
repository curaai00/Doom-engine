#include "../src/util_draw.h"
#include "gtest/gtest.h"

TEST(UtilDraw, GetPixel)
{
    const auto img = IMG_Load("resource/gradation.png");
    auto pixel = util::draw::get_pixel(img, 0, 0);
    EXPECT_EQ(pixel.r, 255);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
    EXPECT_EQ(pixel.a, 255);
}