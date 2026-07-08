#include <iostream>
#include <ArrayGL/ArrayGL.h>

int main() {
    window(800, 600, vector<int>{255, 0, 255}, "hello world!");
    Array arr1 = make_array(10, 5, 16, RED, true);
    Pixel pixel1 = make_pixel(10, 20, 30, 30, BLACK);

    pixel1.WASD_input(10.0);    

    while (run()) {

    }

    return 0;
}