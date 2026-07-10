#include "../include/ArrayGL/shader.h"
#include <fstream>
#include <sstream>

void Shader::compile() {
    GLuint vs, fs;
    GLint success;
    GLchar info_log[512];

    const GLchar* vs_code = "#version 460 core\n"
                    "layout (location = 0) in vec2 pos;\n"
                    "uniform mat4 projection;\n"
                    "void main() {\n"
                        "gl_Position = projection * vec4(pos, 0.0, 1.0);\n"
                    "}";

    const GLchar* fs_code = "#version 460 core\n"
                    "out vec4 PixelColor;\n"
                    "uniform vec3 color;\n"
                    "void main() {\n"
                        "PixelColor = vec4(color, 1.0);\n"
                    "}";

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_code, nullptr);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, nullptr, info_log);
        cerr << "FAILED TO COMPILE VERTEX SHADER: " << endl;
        cerr << info_log << endl;
        throw;
    }
    

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1,&fs_code, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, nullptr, info_log);
        cerr << "FAILED TO COMPILE FRAGMENT SHADER: " << endl;
        cerr << info_log << endl;
        throw;
    }


    id_ = glCreateProgram();
    glAttachShader(id_, vs);
    glAttachShader(id_, fs);
    glLinkProgram(id_);

    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, nullptr, info_log);
        cerr << "FAILED TO LINK PROGRAM" << endl;
        cerr << info_log << endl;
        throw;

    }

    glDeleteShader(vs);
    glDeleteShader(fs);


}

void Shader::use() {
    compile();
    glUseProgram(id_);
}


void Shader::set_bool(const GLchar* name, GLboolean value) {
    glUniform1i(glGetUniformLocation(id_, name), value);
}

void Shader::set_int(const GLchar* name, GLint value) {
    glUniform1i(glGetUniformLocation(id_, name), value);
}

void Shader::set_float(const GLchar* name, GLfloat value) {
    glUniform1f(glGetUniformLocation(id_, name), value);
}

void Shader::set_vec2(const GLchar* name, glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(id_, name), 1, &value[0]);
}

void Shader::set_vec3(const GLchar* name, glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(id_, name), 1, &value[0]);
}

void Shader::set_mat4(const GLchar* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, &matrix[0][0]);
}

