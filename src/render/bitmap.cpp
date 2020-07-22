#include "bitmap.h"
#include "colour.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstddef>
#include <stdexcept>
#include <string>

Bitmap::Bitmap(const std::string& path)
{
    int width;
    int height;
    int channel_amount;

    unsigned char* image_bytes = stbi_load(path.c_str(), &width, &height, &channel_amount, 3);
    if (image_bytes == nullptr) {
        stbi_image_free(image_bytes);
        throw std::runtime_error("Could not load bitmap " + path);
    }

    for (std::size_t i = 0; i < width * height * channel_amount; ++i) {
        bytes_.push_back(image_bytes[i]);
    }

    width_ = width;
    height_ = height;
    channels_ = channel_amount;

    std::vector<unsigned char> tmp{};
    tmp.reserve(bytes_.size());
    tmp.resize(bytes_.size());

    // Flip the image on y-axis
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            tmp.at((x+y*width)*3) = bytes_.at((x+(height - y - 1) * width) * 3);
            tmp.at((x+y*width)*3+1) = bytes_.at((x+(height - y - 1) * width) * 3+1);
            tmp.at((x+y*width)*3+2) = bytes_.at((x+(height - y - 1) * width) * 3+2);
        }
    }

    bytes_ = tmp;

    stbi_image_free(image_bytes);
}

Colour Bitmap::get_pixel(int x, int y) const
{
    Colour c{};

    std::size_t offset = (x + y * width_) * 3;

    c.r = static_cast<int>(bytes_[offset + 0]);
    c.g = static_cast<int>(bytes_[offset + 1]);
    c.b = static_cast<int>(bytes_[offset + 2]);

    return c;
}

int Bitmap::width() const
{
    return width_;
}

int Bitmap::height() const
{
    return height_;
}
