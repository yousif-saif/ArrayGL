#include "../include/ArrayGL/pixel.h"
#include "../include/ArrayGL/render.h"


Pixel::Pixel(float x, float y, float width, float height, vector<int> color, int z_index, Renderer *renderer) 
    : x(x), y(y), width(width), height(height), color(color), z_index(z_index)
{   
    
    pixelDest = {x, y, width, height};
    
    if (renderer != nullptr) {
        renderer->pixels_buffer.push_back(this);
    }

}


bool Pixel::collision(Pixel pixel2) {
    bool horizontalOverlap = (this->x + this->width >= pixel2.x) && (this->x <= pixel2.x + pixel2.width);    
    bool verticalOverlap =   (this->y + this->height >= pixel2.y) && (this->y <= pixel2.y + pixel2.height);
    return horizontalOverlap && verticalOverlap;
    
}


void Pixel::WASD_input(float speed) {
    Pixel::input_mode = "WASD";
    Pixel::speed = speed;
}

void Pixel::arrows_input(float speed) {
    Pixel::input_mode = "ARROWS";
    Pixel::speed = speed;
}