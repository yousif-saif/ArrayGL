#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <glm/ext/matrix_clip_space.hpp>
#include <stb/stb_image.h>
#include "./headers/shader.h"
#include "./headers/texture.h"
// #include "./headers/material.h"
#include "./headers/render.h"
// #include "./headers/EC/entity.h"
#include "./headers/pixel.h"
#include "./headers/array.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <thread>
#include <chrono>

using namespace std;
// #define 800 800
// #define 600 600

void getInput(GLFWwindow* window, float &x, float &y);

// void processInput(GLFWwindow* window);
// Rect charater_dest = { 5, 5, 128, 128 };
// Rect charater_dest2 = { 800 - 69, 600 - 69, 64, 64 };
// Rect src = { 0, 0, 64, 64 };

constexpr auto SPEED = 0.1f;

int main() {
    if (!glfwInit()) {
        cerr << "GLFW FAILED TO INIT!" << endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(800, 600, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "FAILED TO LOAD GLAD" << endl;
        return 1;
    }

    glViewport(0, 0, 800, 600);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    const GLchar* pixel_vs_shader_path = "C:/Users/msi/Desktop/arrayGL/shaders/pixel.vs";
    const GLchar* pixel_fs_shader_path = "C:/Users/msi/Desktop/arrayGL/shaders/pixel.fs";

    Shader shader;
    shader.load(pixel_vs_shader_path, pixel_fs_shader_path);
    shader.use();


    auto projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, -1.0f);
    shader.set_mat4("projection", projection);

    // Pixel pixel(0, 1, {2, 3, 4});
    // glm::vec3 color{0.5, 0.8, 0.0};
    // Pixel pixel(0.0, 0.0, 32.0, 32.0, {color[0], color[1], color[2]});
    // Pixel pixel2(32.0, 0.0, 32.0, 32.0, {color[0], color[1], color[2]});
    

    Array array1(10, 10, 32, glm::vec3(0.1, 0.5, 0.7), false, 1);
    Array array2(9, 9, 32, glm::vec3(0.2, 0.4, 0.2), false, 2);
    Array array3(8, 8, 32, glm::vec3(0.5, 0.8, 0.4), false, 3);
    Array array4(7, 7, 32, glm::vec3(0.2, 0.9, 0.7), false, 4);


    pair<Pixel, Pixel> player = make_pair(array1[9][1], array1[8][1]);
    Renderer renderer = Renderer(vector<GLuint>{2, 2}, 128, shader);
    // shader.set_vec3("color", color);

    glm::vec3 color{1.0, 0.0, 0.0};
    player.first.color = vector<float>{color[0], color[1], color[2]};
    

    glm::vec3 color2{0.5, 1.0, 1.0};
    player.second.color = vector<float>{color2[0], color2[1], color2[2]};

    vector<Pixel> pixels = {
        Pixel(100, 10, 32, 32, vector<float>{0.5, 1.0, 0.1}),
        Pixel(100, 30, 32, 32, vector<float>{0.5, 0.8, 1.0}),
        Pixel(100, 50, 32, 32, vector<float>{1.0, 0.5, 1.0})

    };

    Entity ent1(5, 7, &array1, &renderer);
    Entity ent2(1, 2, &array2, &renderer);
    Entity ent3(1, 2, &array3, &renderer);
    Entity ent4(1, 2, &array4, &renderer);

    cout << renderer.entities.size() << endl;
    while (!glfwWindowShouldClose(window)) {
        // auto frameStart = chrono::steady_clock::now();

        // processInput(window);
        glClearColor(255.0f, 0.0f, 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // renderer.begin();
        // renderer.drawArray(array);
        renderer.drawPixel(player.first);
        renderer.drawPixel(player.second);
        renderer.drawEntities();

        getInput(window, player.first.x, player.first.y);
        getInput(window, player.second.x, player.second.y);



        // renderer.end();

        // auto frameEnd = std::chrono::steady_clock::now();
        // chrono::duration<double, milli> elapsed = frameEnd - frameStart;

        // double fps = 60;
        // double milliseconds = 1000/fps;
        // double sleepTime = milliseconds - elapsed.count;

        glfwSwapBuffers(window);
        glfwPollEvents();

        this_thread::sleep_for(chrono::milliseconds(1));
    }

    // delete e_game;
    glfwTerminate();
    cout << "HELLO WORLD" << endl;
    return 0;

}


void getInput(GLFWwindow* window, float &x, float &y) {
    float speed = 10;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { y -= speed; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { y += speed; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { x -= speed; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { x += speed; }


}