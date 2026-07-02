#include "./headers/pixel.h"


Pixel::Pixel(float x, float y, float w, float h, vector<float> color, int z_index) 
    : x(x), y(y), w(w), h(h), color(color), z_index(z_index)
{
    pixelDest = {x, y, w, h};

}
