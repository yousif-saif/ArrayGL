#include "./headers/render.h"
#include "./headers/pixel.h"
#include "./headers/array.h"
#include <algorithm>

using namespace std;

constexpr auto VERTICES = 6u;

Renderer::Renderer(vector<GLuint> attributes, GLuint max_sprites, Shader shader) 
    : VBO_(0), VAO_(0), max_sprites_(max_sprites), shader(shader)

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



Entity::Entity(float x, float y, Array* array, Renderer* renderer)
	: x(x), y(y), array(array), renderer(renderer)
{
	cout << "ARRAY" << endl;
	renderer->entities.push_back(this);
}


void Entity::draw() {
	renderer->drawEntities();
}



void print_z_index(vector<Pixel> pixels) {
	for (Pixel pixel : pixels) {
		cout << pixel.z_index << endl;
	}

}


void sortByZIndex(vector<Pixel> &pixels) {
	sort(pixels.begin(), pixels.end(), [](const Pixel& a, const Pixel& b) {
		return a.z_index < b.z_index;
	});
}

void Renderer::drawEntities() {
	sort(entities.begin(), entities.end(), [](const Entity* a, const Entity* b) {
		return a->array->z_index < b->array->z_index;
	});

	for (Entity* i : entities) {
		if (i == nullptr) {
			continue;
		}

		vector<Pixel> pixels;
		if (i->array != nullptr) {
			pixels = i->array->data;
		}

		for (Pixel pixel : pixels) {
			drawPixel(pixel);
		}

	}
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
	buffers_[bufferType].push_back(dest.y + dest.h);
	buffers_[bufferType].push_back(src.x);
	buffers_[bufferType].push_back(src.y + src.h);

	// top right
	buffers_[bufferType].push_back(dest.x + dest.w);
	buffers_[bufferType].push_back(dest.y);
	buffers_[bufferType].push_back(src.x + src.w);
	buffers_[bufferType].push_back(src.y);

	// top left
	buffers_[bufferType].push_back(dest.x);
	buffers_[bufferType].push_back(dest.y);
	buffers_[bufferType].push_back(src.x);
	buffers_[bufferType].push_back(src.y);

	// second triangle

	// top left
	buffers_[bufferType].push_back(dest.x);
	buffers_[bufferType].push_back(dest.y + dest.h);
	buffers_[bufferType].push_back(src.x);
	buffers_[bufferType].push_back(src.y + src.h);

	// top right
	buffers_[bufferType].push_back(dest.x + dest.w);
	buffers_[bufferType].push_back(dest.y + dest.h);
	buffers_[bufferType].push_back(src.x + src.w);
	buffers_[bufferType].push_back(src.y + src.h);

	// top right
	buffers_[bufferType].push_back(dest.x + dest.w);
	buffers_[bufferType].push_back(dest.y);
	buffers_[bufferType].push_back(src.x + src.w);
	buffers_[bufferType].push_back(src.y);


}


void Renderer::drawPixel(Pixel pixel) {
	string bufferType = "pixel";

	glm::vec3 color(pixel.color[0], pixel.color[1], pixel.color[2]);
	shader.set_vec3("color", color);

	generate_buffer(Rect{pixel.x, pixel.y, pixel.w, pixel.h}, pixel.pixelSrc, "pixel");
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

