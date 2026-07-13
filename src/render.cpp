#include <algorithm>

#include "../include/ArrayGL/render.h"
#include "../include/ArrayGL/pixel.h"
#include "../include/ArrayGL/array.h"

using namespace std;

constexpr auto VERTICES = 6u;

Renderer::Renderer(GLFWwindow *window, Shader shader) 
    : VBO_(0), VAO_(0), shader(shader)

{
    att_size_ = 0;
    for (auto att : attributes) att_size_ += att;

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    auto stride = 0ull;
    for (auto i = 0ull; i < attributes.size(); i++) {
        glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, 
            att_size_ * sizeof(GLfloat), (GLvoid*)stride);
        glEnableVertexAttribArray(i); // the location number in vertex shader
        stride += sizeof(GLfloat) * attributes[i];

    }

}


void move_WASD(GLFWwindow* window, float &x, float&y, float speed) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { y -= speed; }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { y += speed; }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { x -= speed; }
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { x += speed; }
}

void move_arrows(GLFWwindow* window, float &x, float&y, float speed) {
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { y -= speed; }
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { y += speed; }
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { x -= speed; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { x += speed; }	
}

void sort_by_z_index(vector<Array*> &arrays_buffer) {
	stable_sort(arrays_buffer.begin(), arrays_buffer.end(), [](const Array* a, const Array* b) {
		return a->z_index < b->z_index;
	});
}

void sort_by_z_index(vector<Pixel*> &pixels_buffer) {
	stable_sort(pixels_buffer.begin(), pixels_buffer.end(), [](const Pixel* a, const Pixel* b) {
		return a->z_index < b->z_index;
	});
}

void sort_by_z_index(vector<final_buffer> &pixels_buffer) {
	stable_sort(pixels_buffer.begin(), pixels_buffer.end(), [](const final_buffer a, const final_buffer b) {
		return a.z_index < b.z_index;
	});
}

void Renderer::drawBuffers() {
	// Draw arrays buffer
	if (arrays_buffer.size() >= 1) {
		// sort by z-index to render arrays in a specific stacked order
		// sort_by_z_index(arrays_buffer);
		for (Array* i : arrays_buffer) {
			if (i == nullptr) {
				continue;
			}

			if (i->input_mode == "WASD") {
				move_WASD(window, i->x, i->y, i->speed);
			} else if (i->input_mode == "ARROWS") {
				move_arrows(window, i->x, i->y, i->speed);
			}

			for (Pixel pixel : i->data) {
				Rect dims{
					pixel.x + i->x,
					pixel.y + i->y,
					pixel.width,
					pixel.height
				};

				final_buffer draw = {dims, pixel.color, pixel.z_index};
				draw_buffer.push_back(draw);

				// drawPixel(Pixel(
				// 	pixel.x + i->x,
				// 	pixel.y + i->y,
				// 	pixel.width,
				// 	pixel.height,
				// 	pixel.color,
				// 	pixel.z_index
				// ));

			}

		}

	}

	// Draw pixels buffer
	if (pixels_buffer.size() >= 1) {
		// sort_by_z_index(pixels_buffer);

		for (Pixel* i : pixels_buffer) {
			if (i == nullptr) {
				continue;
			}
			Pixel pixel = *i;
			if (i->input_mode == "WASD") {
				move_WASD(window, i->x, i->y, i->speed);
			} else if (i->input_mode == "ARROWS") {
				move_arrows(window, i->x, i->y, i->speed);
			}
			
			Rect dims{
				pixel.x,
				pixel.y,
				pixel.width,
				pixel.height
			};

			final_buffer draw{dims, pixel.color, pixel.z_index};
			draw_buffer.push_back(draw);
			// drawPixel(*i);

		}
	}


	if (draw_buffer.size() >= 1) {
		sort_by_z_index(draw_buffer);
		for (final_buffer i : draw_buffer) {
			drawPixel(i);
		}
	}

	draw_buffer.clear();
	
}



Renderer::~Renderer() {
    if (VBO_)
		glDeleteBuffers(1, &VBO_);
	if (VAO_)
		glDeleteBuffers(1, &VAO_); 

    VBO_ = 0;
    VAO_ = 0;
}


void Renderer::generate_buffer(Rect dest, Rect src, string bufferType) {
	
	if (buffers_.count(bufferType) <= 0) {
		buffers_[bufferType] = vector<GLfloat>{};
	}


	// first triangle

	// top left
	buffers_[bufferType].push_back(dest.x);
	buffers_[bufferType].push_back(dest.y + dest.height);
	buffers_[bufferType].push_back(src.x);
	buffers_[bufferType].push_back(src.y + src.height);

	// top right
	buffers_[bufferType].push_back(dest.x + dest.width);
	buffers_[bufferType].push_back(dest.y);
	buffers_[bufferType].push_back(src.x + src.width);
	buffers_[bufferType].push_back(src.y);

	// top left
	buffers_[bufferType].push_back(dest.x);
	buffers_[bufferType].push_back(dest.y);
	buffers_[bufferType].push_back(src.x);
	buffers_[bufferType].push_back(src.y);

	// second triangle

	// top left
	buffers_[bufferType].push_back(dest.x);
	buffers_[bufferType].push_back(dest.y + dest.height);
	buffers_[bufferType].push_back(src.x);
	buffers_[bufferType].push_back(src.y + src.height);

	// top right
	buffers_[bufferType].push_back(dest.x + dest.width);
	buffers_[bufferType].push_back(dest.y + dest.height);
	buffers_[bufferType].push_back(src.x + src.width);
	buffers_[bufferType].push_back(src.y + src.height);

	// top right
	buffers_[bufferType].push_back(dest.x + dest.width);
	buffers_[bufferType].push_back(dest.y);
	buffers_[bufferType].push_back(src.x + src.width);
	buffers_[bufferType].push_back(src.y);


}


void Renderer::drawPixel(final_buffer buf) {
	string bufferType = "pixel";

	glm::vec3 color(buf.color[0], buf.color[1], buf.color[2]);
	shader.set_vec3("color", color);

	generate_buffer(Rect{buf.dims.x, buf.dims.y, buf.dims.width, buf.dims.height}, Rect{0, 0, 0, 0 }, "pixel");
	this->flush(bufferType);
	didRender[bufferType] = true;

}

void Renderer::flush(string bufferType) {
	vector<GLfloat> &buffer_ = buffers_[bufferType];
	if (buffer_.empty()) return;


	glBindVertexArray(this->VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*buffer_.size(), buffer_.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, buffer_.size() / this->att_size_);
    buffer_.clear();
}

