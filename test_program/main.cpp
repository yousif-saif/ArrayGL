#include "../include/ArrayGL/texture.h"
#include "../include/ArrayGL/shader.h"
#include "../include/ArrayGL/render.h"
#include "../include/ArrayGL/pixel.h"
#include "../include/ArrayGL/array.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/glm.hpp> 
#include <iostream>
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
    cout << "Hello ArrayGL!" << endl;

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

    const char* pixel_vs_shader_path = "shaders/pixel.vs";
    const char* pixel_fs_shader_path = "shaders/pixel.fs";

    Shader shader;
    shader.load(pixel_vs_shader_path, pixel_fs_shader_path);
    shader.use();



    Renderer renderer = Renderer(shader);    
    Array array1(10, 10, 32, glm::vec3(0.1, 0.5, 0.7), &renderer, true, 2);
    Array array2(4, 9, 32, glm::vec3(0.2, 0.4, 0.2), &renderer, true, 1);
    array2.x = array1.width;
    array2.y = array1.height;


    while (!glfwWindowShouldClose(window)) {
        glClearColor(255.0f, 0.0f, 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.set_mat4("projection", projection);

        renderer.drawBuffers();
        WASD_input(window, array1.x, array1.y);
        arrows_input(window, array2.x, array2.y);


        glfwSwapBuffers(window);
        glfwPollEvents();

        this_thread::sleep_for(chrono::milliseconds(1));
    }

    glfwTerminate();
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