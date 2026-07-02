#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "./rect.h"

using namespace std;

class Pixel {        
    public:
        float x, y, w, h;
        int z_index;
        vector<float> color;
        Rect pixelDest;
        Rect pixelSrc = { 0, 0, 0, 0 }; // test values
        Pixel(float x, float y, float w, float h, vector<float> color, int z_index=0);

};