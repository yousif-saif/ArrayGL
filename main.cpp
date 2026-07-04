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
#include "./headers/render.h"
#include "./headers/pixel.h"
#include "./headers/array.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <thread>
#include <chrono>

using namespace std;

void WASD_input(GLFWwindow* window, float &x, float &y);
void arrows_input(GLFWwindow* window, float &x, float &y);

constexpr auto SPEED = 0.1f;

glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, -1.0f);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, -1.0f);
    glViewport(0, 0, width, height);
}


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

    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    
    const GLchar* pixel_vs_shader_path = "C:/Users/msi/Desktop/arrayGL/shaders/pixel.vs";
    const GLchar* pixel_fs_shader_path = "C:/Users/msi/Desktop/arrayGL/shaders/pixel.fs";

    Shader shader;
    shader.load(pixel_vs_shader_path, pixel_fs_shader_path);
    shader.use();



    Renderer renderer = Renderer(vector<GLuint>{2, 2}, 128, shader);
    
    // FIX THE LINES WHEN CHANING DIMESNSIONS
    Array array1(10, 5, 32, glm::vec3(0.1, 0.5, 0.7), &renderer, true, 1);
    Array array2(4, 9, 32, glm::vec3(0.2, 0.4, 0.2), &renderer, false, 2);
    array2.x = array1.width;
    array2.y = array1.height;

    // Array array3(8, 8, 32, glm::vec3(0.5, 0.8, 0.4), &renderer, false, 3);
    // Array array4(7, 7, 32, glm::vec3(0.2, 0.9, 0.7), &renderer, false, 4);

    // pair<Pixel, Pixel> player = make_pair(array1[9][1], array1[8][1]);
    // glm::vec3 color{1.0, 0.0, 0.0};
    // player.first.color = vector<float>{color[0], color[1], color[2]};
    

    // glm::vec3 color2{0.5, 1.0, 1.0};
    // player.second.color = vector<float>{color2[0], color2[1], color2[2]};

    // vector<Pixel> pixels = {
    //     Pixel(100, 10, 32, 32, vector<float>{0.5, 1.0, 0.1}),
    //     Pixel(100, 30, 32, 32, vector<float>{0.5, 0.8, 1.0}),
    //     Pixel(100, 50, 32, 32, vector<float>{1.0, 0.5, 1.0})

    // };


    while (!glfwWindowShouldClose(window)) {
        glClearColor(255.0f, 0.0f, 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.set_mat4("projection", projection);

        // renderer.drawPixel(player.first);
        // renderer.drawPixel(player.second);
        renderer.drawBuffers();

        // WASD_input(window, player.first.x, player.first.y);
        // WASD_input(window, player.second.x, player.second.y);
        WASD_input(window, array1.x, array1.y);
        arrows_input(window, array2.x, array2.y);


        glfwSwapBuffers(window);
        glfwPollEvents();

        this_thread::sleep_for(chrono::milliseconds(1));
    }

    glfwTerminate();
    cout << "HELLO WORLD" << endl;
    return 0;

}


void WASD_input(GLFWwindow* window, float &x, float &y) {
    float speed = 10;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { y -= speed; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { y += speed; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { x -= speed; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { x += speed; }

}

void arrows_input(GLFWwindow* window, float &x, float &y) {
    float speed = 10;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { y -= speed; }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { y += speed; }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { x -= speed; }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { x += speed; }

}