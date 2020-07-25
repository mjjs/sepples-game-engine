#ifndef _SGE_COLOUR_H
#define _SGE_COLOUR_H

#include <iostream>

struct Colour {
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 255;

    bool is_black();
};

std::ostream& operator<<(std::ostream& os, const Colour& colour);

#endif
