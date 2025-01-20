#ifndef COLORS_H
#define COLORS_H

#include <raylib.h>
#include <vector>

inline std::vector<Color> getCellColors()
{
    return {DARKGRAY, GREEN, RED, ORANGE, YELLOW, PURPLE, SKYBLUE, BLUE};
}

#endif // COLORS_H