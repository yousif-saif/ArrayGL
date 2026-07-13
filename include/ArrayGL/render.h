#pragma once

#include "shader.h"
#include "array.h"
#include "pixel.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <map>
#include <any>

using namespace std;

struct final_buffer {
    Rect dims;
    vector<int> color;
    int z_index;
};

class Renderer {
    GLuint VBO_, VAO_, att_size_, max_arrays_;
    map<string, vector<GLfloat>> buffers_;
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
        vector<final_buffer> draw_buffer;

        void begin();
        void end();
        void generate_buffer(Rect dest, Rect src, string bufferType);
        void drawPixel(final_buffer buf);
        void drawBuffers();
        void listen_for_keybord();
        void flush(string bufferType);
};
