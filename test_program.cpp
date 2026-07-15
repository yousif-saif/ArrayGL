#include <iostream>
#include <ArrayGL/ArrayGL.h>


void array_callback() {
    cout << "Executing Array callback" << endl;
}

void pixel_callback() {
    cout << "Executing Pixel callback" << endl;
}

int main() {
    GLFWwindow* window_ = window(800, 600, vector<int>{255, 192, 203}, "hello world!");
    Array arr1 = make_array(10, 5, 16, RED, true, 1);
    Pixel pixel1 = make_pixel(10, 20, 30, 30, BLACK, 0);
    pixel1.arrows_input(10.0);
    arr1.WASD_input(10.0);

    add_callback(arr1, array_callback);
    add_callback(pixel1, pixel_callback);

    while (run()) {}

    return 0;
}