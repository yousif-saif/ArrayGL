#pragma once

#include "shader.h"
#include "array.h"
#include "pixel.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <map>

// #include "ArrayGL.h"
using namespace std;


// class Entity;

class Renderer {
    GLuint VBO_, VAO_, att_size_, max_arrays_;
    map<string, vector<GLfloat>> buffers_; // buffer type, buffer
    map<string, bool> didRender;
    Shader shader;

    public:
        GLFWwindow* window;

        vector<GLuint> attributes{2, 2};
        GLuint max_arrays = 128;

        Renderer(GLFWwindow *window, Shader shader);
        ~Renderer();

        // vector<Entity*> entities;
        vector<Array*> arrays_buffer;
        vector<Pixel*> pixels_buffer;

        void begin();
        void end();
        void generate_buffer(Rect dest, Rect src, string bufferType);
        void drawPixel(const Pixel &pixel);
        void drawBuffers();
        void listen_for_keybord();
        void flush(string bufferType);
};


// class Entity {
//     public:
//         float x, y;
//         Array* array;
//         Renderer* renderer;
//         Entity(float x, float y, Array* array, Renderer* renderer);

//         void draw();

// };

