#pragma once


#include "array.h"
#include "pixel.h"
#include "rect.h"
#include "render.h"


#include <glm/ext/matrix_clip_space.hpp>
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp> 
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;


#define voidFunc function<void (void)>

#define RED vector<int>{255, 0, 0}
#define BLUE vector<int>{0, 0, 255}
#define GREEN vector<int>{0, 255, 0}
#define BLACK vector<int>{0, 0, 0}
#define WHITE vector<int>{255, 255, 255}

vector<float> scale_down_color(
    vector<int> RGB
);

GLFWwindow* window(
    int width=800,
    int height=600,
    vector<int> color=BLACK,
    string title="ArrayGL Window"
);

bool run(
    bool use_max_gpu=false
);

void WASD_input(
    Array& arr, 
    float speed
);

void arrows_input(
    Array& arr, 
    float speed
);

Array make_array(
    int rows=10,
    int cols=10,
    int pixelSize=32,
    vector<int> color=BLACK,
    bool show_lines=false,
    int z_index=0
);

Pixel make_pixel(
    float x=0,
    float y=0,
    float w=32,
    float h=32,
    vector<int> color=BLACK,
    int z_index=0
);


void add_callback(Array &arr, voidFunc callback);
void add_callback(Pixel &pixel, voidFunc callback);
