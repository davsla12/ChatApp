#ifndef SPRITES_H
#define SPRITES_H
#include <iostream>

struct Sprite {
    int y = 2;
    int x = 7;
    int color_pair = 0;
    int high = 1;
    int width = 2;
    std::string mask = "{}";

};

#endif
