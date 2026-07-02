#include "./headers/render.h"
#include "./headers/pixel.h"
#include "./headers/array.h"
#include <algorithm>

using namespace std;

constexpr auto VERTICES = 6u;

Renderer::Renderer(vector<GLuint> attributes, GLuint max_sprites, Shader shader) 
    // : VBO_(0), VAO_(0), curr_mat_(nullptr), max_sprites_(max_sprites), shader(shader)
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


// Entity::Entity(float x, float y, vector<Pixel> *pixels, Renderer* renderer)
// 	: x(x), y(y), array(nullptr), renderer(renderer)
// {
// 	cout << "PIXELS" << endl;
// 	renderer->entities.push_back(this);
// }


Entity::Entity(float x, float y, Array* array, Renderer* renderer)
	: x(x), y(y), array(array), renderer(renderer)
{
	cout << "ARRAY" << endl;
	renderer->entities.push_back(this);
}


// Entity::Entity(float x, float y, vector<Pixel> pixels, Renderer* renderer) {
	// cout << "PIXELS" << endl;
	// renderer->entities.push_back(this);
	
// }

// Entity::Entity(float x, float y, Array* array, Renderer* renderer) {
	// cout << "ARRAY" << endl;
	// renderer->entities.push_back(this);
// }


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
		// if (i->pixels != nullptr) {
		// 	pixels = *(i->pixels);
		// 	cout << "PIXEL COUNT INSIDE PIXEL: " << pixels.size() << endl;
		// }

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


// void Renderer::draw(Rect dest, Rect src, Material& mat) {
// 	string bufferType = "material";
// 	int bufferSize = buffers_.count(bufferType) == 0 ? 0 : buffers_[bufferType].size();

//     // Dest: position (x, y)
//     // Src: Texture coords (u, v)

	
// 	if ((bufferSize >= static_cast<size_t>(this->max_sprites_) * this->max_sprites_ * VERTICES || !this->curr_mat_) 
// 		|| this->curr_mat_->id != mat.id)
// 	{
// 		// flush out current batch and start on the next one
// 		this->flush(bufferType);
// 		this->curr_mat_ = &mat;
// 	}


// 	auto norm_src = src;
// 	auto image_w = mat.texture.width;
// 	auto image_h = mat.texture.height;

// 	norm_src.x /= image_w;
// 	norm_src.w /= image_w;

// 	norm_src.y /= image_h;
// 	norm_src.h /= image_h;

// 	generate_buffer(dest, norm_src, bufferType);

// }


void Renderer::drawPixel(Pixel pixel) {
	string bufferType = "pixel";
	// int bufferSize = buffers_.count(bufferType) == 0 ? 0 : buffers_[bufferType].size();

	// if (bufferSize >= static_cast<size_t>(this->max_sprites_) * this->max_sprites_ * VERTICES)
	// {
	// 	// flush out current batch and start on the next one
	// 	this->flush(bufferType);
	// }

	glm::vec3 color(pixel.color[0], pixel.color[1], pixel.color[2]);
	shader.set_vec3("color", color);

	generate_buffer(Rect{pixel.x, pixel.y, pixel.w, pixel.h}, pixel.pixelSrc, "pixel");
	this->flush(bufferType);
	didRender[bufferType] = true;

}


// void Renderer::drawArray(Array array) {
// 	string bufferType = "pixel";
// 	// print_z_index(array.data);

// 	// sortByZIndex(array.data);

// 	// print_z_index(array.data);

// 	for (Pixel pixel : array.data) {
// 		drawPixel(pixel);
// 	}

// 	this->flush(bufferType);
// 	didRender[bufferType] = true;

// }


// void print(vector<GLfloat> arr) {
//     for (int i=0; i < arr.size(); i++) {
//         cout << arr[i] << endl;
//     }

// }

void Renderer::flush(string bufferType) {
	vector<GLfloat> &buffer_ = buffers_[bufferType];
	if (buffer_.empty()) return;



	glBindVertexArray(this->VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_);

	// if (bufferType == "material") {
	// 	if(!this->curr_mat_) {
	// 		buffer_.clear();
	// 		return;
	// 	}

	// 	this->curr_mat_->compile();
	// 	this->curr_mat_->bind();
	// }

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*buffer_.size(), buffer_.data(), GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, buffer_.size() / this->att_size_);
    buffer_.clear();
}

// void Renderer::begin() {
//     this->curr_mat_ = nullptr;
    
// }



// void Renderer::end() {
// 	for (auto& buffer : buffers_) {
// 		if (didRender.count(buffer.first) > 0) {
// 			continue;
// 		}
//     	this->flush(buffer.first); // pass the bufferType

// 	}

// 	didRender.clear();

// }