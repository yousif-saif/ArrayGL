#pragma once

#include "rect.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <vector>

#define voidFunc function<void (void)>

using namespace std;
class Renderer;
class Pixel {        
    public:
        float x, y, width, height;
        int z_index;
        vector<int> color;
        string input_mode;
        float speed;
        Rect pixelDest;
        Rect pixelSrc = { 0, 0, 0, 0 };
        voidFunc cb;
        bool has_cb = false;
        Pixel(float x, float y, float w, float h, vector<int> color, int z_index=0, Renderer *renderer=nullptr);
        bool collision(Pixel pixel2);
        void WASD_input(float speed);
        void arrows_input(float speed);

};