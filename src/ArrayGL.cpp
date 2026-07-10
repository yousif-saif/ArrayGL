#include "../include/ArrayGL/ArrayGL.h"


glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, -1.0f);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, -1.0f);
    glViewport(0, 0, width, height);
}

GLFWwindow* window_;
Shader shader;
Renderer *renderer = nullptr;
vector<float> color_scaled;

void terminate_program() {
    delete renderer;
    glfwDestroyWindow(window_);
    glfwTerminate();
}


vector<float> scale_down_color(vector<int> RGB) {
    vector<float> result;
    for (int channel : RGB) {
        result.push_back(channel/255.0);
    }
    return result;
}

GLFWwindow* window(int width, int height, vector<int> color, string title) {    
    if (!glfwInit()) {
        cerr << "GLFW FAILED TO INIT!" << endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "FAILED TO LOAD GLAD" << endl;
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window_, frame_buffer_size_callback);
    shader.use();

    color_scaled = scale_down_color(color);
    renderer = new Renderer(window_, shader);


    return window_;
}

Array make_array(
    int rows,
    int cols,
    int pixelSize,
    vector<int> color,
    bool show_lines,
    int z_index
) {
    // vector<float> array_color = scale_down_color(color);
    
    if (renderer != nullptr) {
        return Array(
            rows,
            cols,
            pixelSize,
            color,
            renderer,
            show_lines,
            z_index
        );
    } else {
        cout << "Can't render array, Renderer (window) isn't initialized yet." << endl;
        terminate_program();
        exit(0);
    }
}


Pixel make_pixel(
    float x,
    float y,
    float w,
    float h,
    vector<int> color,
    int z_index
) {
    if (renderer != nullptr) {
        return Pixel(
            x,
            y,
            w, 
            h,
            color,
            z_index,
            renderer
        );

    } else {
        cout << "Can't render pixel, Renderer (window) isn't initialized yet." << endl;
        terminate_program();
        exit(0);
    }

}


bool run(bool use_max_gpu) {
    if (renderer == nullptr) {
        cout << "Renderer hasn't been initialized yet." << endl;
        terminate_program();
        return false;
    }

    // while (!glfwWindowShouldClose(window_)) {
    glClearColor(
        color_scaled[0],
        color_scaled[1],
        color_scaled[2],
        1.0f
    );
    glClear(GL_COLOR_BUFFER_BIT);

    shader.set_mat4("projection", projection);
    renderer->drawBuffers();

    renderer->window = window_;
    glfwSwapBuffers(window_);
    glfwPollEvents();

    if (!use_max_gpu) this_thread::sleep_for(chrono::milliseconds(1));
    // }

    if (glfwWindowShouldClose(window_)) {
        terminate_program();
        return false;
    }
    
    return true;
}