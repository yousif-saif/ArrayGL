#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>

using namespace std;

class Shader {
    GLuint id_;
    string vs_file_path_, fs_file_path_;    
    void compile(const GLchar* vs_data, const GLchar* fs_data);

    public:
        Shader()
            : id_(0)
        {}
        ~Shader() {
            if (id_)
                glDeleteProgram(id_);
                id_ = 0;
        }

        void load(const GLchar* vs_file_path, const GLchar* fs_file_path);
        void use();
        void set_bool(const GLchar* name, GLboolean value);
        void set_int(const GLchar* name, GLint value);
        void set_float(const GLchar* name, GLfloat value);
        void set_vec2(const GLchar* name, glm::vec2 &value);
        void set_vec3(const GLchar* name, glm::vec3 &value);
        void set_mat4(const GLchar* name, const glm::mat4& matrix);

};