# ArrayGL

ArrayGL is a high-level graphics library built in C++ and OpenGL that focuses on making simple games or graphical programs easy to build and with
a few lines of code.    


## How does it work?
ArrayGL renders objects as graphical "2D Arrays" which means you can change any pixel's color, position and other properties by indexing into the array
like how you would in a typical 2D Array.


## Contribute
If you would like to contribute to this project, You are more than welcome to contribute in any way you want!
Fork the repository, Make the changes, Submit a pull request, And wait until your pull request is reviewed!

You can add new features, fix bugs or even report bugs via the Issues tab.

For contribution ideas check out `new_features.md` which has a list of features that have not been implemented yet.

## Reporting bugs
If you encountered a bug, please sibmit an issue in the `Issues` tab in github.
In the Issue description tell us how to reproduce the bug and copy paste your code.

</br>

## Compile and run your program
You can do so by running this command:
```
g++ -g -std=c++17 -I./include -L./lib ./glad.c ./src/*.cpp ./PROGRAM_NAME.cpp -lglfw3dll -o ArrayGL.exe -lopengl32
```

or to make your life easier change the first command inside `compile.bat` to match your program name and then run `./compile.bat` to compile and run your program automatically.

## Docs & how to use
This section will cover how to use this library:

### Getting started
First you need to include the library header:
```
#include <ArrayGL/ArrayGL.h>
```


### Window creation
Function structure and parameters:
```
void window(
    int width=800,
    int height=600,
    vector<int> color=BLACK,
    std::string title="ArrayGL Window"
);
```

Every ArrayGL program must have the `window` function at the top and the `run` function at the very bottom, Add the rest of the code between them like so:
```
#include <iostream>
#include <ArrayGL/ArrayGL.h>

int main() {
    window(800, 600, vector<int>{255, 0, 255}, "hello ArrayGL!");
    // code that needs to run only once (i.e making arrays, pixels...)
    
    while (run()) {
        // code that runs every frame...
    }
    return 0;
}
```

NOTE: If you know how to use OpenGL you can still use the functions it provides.
You can get the "GLFWwindow* window" object like this:
```
GLFWwindow* window_ = window(800, 600, vector<int>{255, 0, 255}, "hello ArrayGL!");
```
for example:
(This is also an example of "code that runs every frame")
```
while (run()) {
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) { arr1.x += 10.0; }
}
```

You can pass `true` to the `run()` function to use 100% of your GPU if you are running intensive operations.
The default is false.
```
bool run(
    bool use_max_gpu=false
);
```

### Pixel objects
Function structure and parameters:
```
Pixel make_pixel(
    float x=0,
    float y=0,
    float w=32,
    float h=32,
    vector<int> color=BLACK,
    int z_index=0
);
```
`z_index` controls which Pixel is shown on top of another, If a pixel has a bigger z_index it will render on top of pixels with lower z_index.

Example usage:
```
Pixel pixel_square = make_pixel(10, 20, 30, 30, BLACK);
Pixel pixel_rectangle = make_pixel(10, 20, 30, 10, BLACK);
```


### Array objects
Function structure and parameters:
```
Array make_array(
    int rows=10,
    int cols=10,
    int pixelSize=32,
    vector<int> color=BLACK,
    bool show_lines=false,
    int z_index=0
);
```

Example usage:
```
Array square = make_array(10, 10, 16, RED, false);
```
This will create an Array object and automatically renders it.

</br>

Indexing into the array (this will return a Pixel object):
```
square[row][column]
```

Examples:
```
square[5][1].x = 50;
square[5][1].y = 30;
square[5][1].w = 100;
square[5][1].h = 100;
square[5][1].color = BLACK; // pre-defined colors
square[5][1].color = vector<int>{24, 224, 120}; // Custom RGB colors
```


### Making your Arrays/Pixels move
You can control Arrays/Pixels by calling the property `WASD_input(float speed)` or `arrows_input(float speed)`.

For example:
```
square.WASD_input(10.0);
pixel_square.WASD_input(10.0);

square.arrows_input(10.0);
pixel_square.arrows_input(10.0);
```

</br>

Have fun using ArrayGL!