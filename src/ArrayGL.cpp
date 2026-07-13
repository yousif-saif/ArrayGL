#include "../include/ArrayGL/ArrayGL.h"
#include <algorithm>

#define voidFunc function<void (void)>



struct Dims {
    float *x;
    float *y;
    float *width;
    float *height;
};

struct left_click_callback {
    Dims dims;
    int z_index;
    voidFunc cb;
};


glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.0f, -1.0f);
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
    projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, -1.0f);
    glViewport(0, 0, width, height);
}

GLFWwindow* window_;
Shader shader;
Renderer *renderer = nullptr;
vector<float> color_scaled;
vector<left_click_callback> left_click_callbacks;


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

Renderer* get_renderer() {
    return renderer;
};

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


bool collision(Dims dims, int x, int y) {
    return (x >= *dims.x && x <= *dims.x + *dims.width && 
            y >= *dims.y && y <= *dims.y + *dims.height);
}


void sort_by_z_index(vector<left_click_callback> &callbacks) {
	sort(callbacks.begin(), callbacks.end(), [](const left_click_callback a, const left_click_callback b) {
		return a.z_index > b.z_index;
	});
}


void add_callback(Array &arr, voidFunc callback) {
    Dims arrDims = {
        &arr.x,
        &arr.y,
        &arr.width,
        &arr.height
    };

    left_click_callbacks.push_back(left_click_callback{arrDims, arr.z_index, callback});
    sort_by_z_index(left_click_callbacks);


}

void add_callback(Pixel &pixel, voidFunc callback) {
    Dims pixDims = {
        &pixel.x,
        &pixel.y,
        &pixel.width,
        &pixel.height
    };

    left_click_callbacks.push_back(left_click_callback{pixDims, pixel.z_index, callback});
    sort_by_z_index(left_click_callbacks);

}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)  {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // collision is checked if the clicked point is inside the object's dimensions
        // so it means if two objects are stacked on top of eachother the callback for both will be called
        // because the clicked point is inside both object's dimensions.
        // TODO: fix when clicking on an Object that doesn't have a callback should stop the click when trying
        // to click an Object that do have a callback but is rendered under it
        vector<left_click_callback> collided; 
        for (left_click_callback i : left_click_callbacks) {
            if (collision(i.dims, xpos, ypos)) { collided.push_back(i); }
        }
        if (!collided.empty()) {
            collided[0].cb(); // only execute the callback of the Object that has the bigger z-index
        }
        
    }
}



bool run(bool use_max_gpu) {
    if (renderer == nullptr) {
        cout << "Renderer hasn't been initialized yet." << endl;
        terminate_program();
        return false;
    }

    glClearColor(
        color_scaled[0],
        color_scaled[1],
        color_scaled[2],
        1.0f
    );
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSetMouseButtonCallback(window_, mouse_button_callback);

    shader.set_mat4("projection", projection);
    renderer->drawBuffers();

    renderer->window = window_;
    glfwSwapBuffers(window_);
    glfwPollEvents();

    if (!use_max_gpu) this_thread::sleep_for(chrono::milliseconds(1));

    if (glfwWindowShouldClose(window_)) {
        terminate_program();
        return false;
    }
    
    return true;
}