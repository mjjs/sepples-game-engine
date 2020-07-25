#include "colour.h"
#include <iostream>

bool Colour::is_black()
{
    return r == 0 && g == 0 && b == 0;
}

std::ostream& operator<<(std::ostream& os, const Colour& colour)
{
    os << "(" << colour.r << "," << colour.g << "," << colour.b << ")";
    return os;
}
