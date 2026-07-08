#include "../include/ArrayGL/pixel.h"
#include "../include/ArrayGL/render.h"


Pixel::Pixel(float x, float y, float w, float h, vector<int> color, int z_index, Renderer *renderer) 
    : x(x), y(y), w(w), h(h), color(color), z_index(z_index)
{
    pixelDest = {x, y, w, h};

    
    if (renderer != nullptr) {
        renderer->pixels_buffer.push_back(this);
    }

}



void Pixel::WASD_input(float speed) {
    Pixel::input_mode = "WASD";
    Pixel::speed = speed;
}

void Pixel::arrows_input(float speed) {
    Pixel::input_mode = "ARROWS";
    Pixel::speed = speed;
}