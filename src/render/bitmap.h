#ifndef _SGE_BITMAP_H
#define _SGE_BITMAP_H

#include "colour.h"
#include <vector>
#include <string>

class Bitmap {
    private:
        std::vector<unsigned char> bytes_;

        int width_;
        int height_;
        int channels_;

    public:
        Bitmap() = default;
        explicit Bitmap(const std::string& path);

        Colour get_pixel(int x, int y) const;
        int width() const;
        int height() const;
};
#endif
