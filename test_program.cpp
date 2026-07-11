#include <iostream>
#include <ArrayGL/ArrayGL.h>


void callback() {
    cout << "FROM TEST_PROGRAM" << endl;
}

int main() {
    GLFWwindow* window_ = window(800, 600, vector<int>{255, 0, 255}, "hello world!");
    Array arr1 = make_array(10, 5, 16, RED, true);
    
    Pixel pixel1 = make_pixel(10, 20, 30, 30, BLACK);
    Pixel pixel2 = make_pixel(50, 20, 70, 30, WHITE);

    pixel1.WASD_input(10.0);
    pixel2.arrows_input(10.0);
    arr1.WASD_input(10.0);

    add_callback(arr1, callback);
    while (run()) {}

    return 0;
}