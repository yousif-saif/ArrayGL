#pragma once
#include <glad/glad.h>
#include <vector>
#include "rect.h"
#include <map>
#include "./pixel.h"
#include "./array.h"
#include "shader.h"
using namespace std;


// class Entity;

class Renderer {
    GLuint VBO_, VAO_, att_size_, max_sprites_;
    map<string, vector<GLfloat>> buffers_; // buffer type, buffer
    map<string, bool> didRender;
    Shader shader;


    public:
        Renderer(vector<GLuint> attributes, GLuint max_sprites, Shader shader);
        ~Renderer();

        // vector<Entity*> entities;
        vector<Array*> arrays_buffer;
        vector<Pixel*> pixels_buffer;

        void begin();
        void end();
        void generate_buffer(Rect dest, Rect src, string bufferType);
        void drawPixel(const Pixel &pixel);
        void drawBuffers();
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

