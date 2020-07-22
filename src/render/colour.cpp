#include "colour.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Colour& colour)
{
    os << "(" << colour.r << "," << colour.g << "," << colour.b << ")";
    return os;
}
