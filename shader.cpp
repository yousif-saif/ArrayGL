#include "./headers/shader.h"
#include <fstream>
#include <sstream>


void Shader::compile(const GLchar* vs_data, const GLchar* fs_data) {
    GLuint vs, fs;
    GLint success;
    GLchar info_log[512];

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_data, nullptr);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, nullptr, info_log);
        cerr << "FAILED TO COMPILE VERTEX SHADER: " << endl;
        cerr << info_log << endl;
        throw;
    }
    

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1,&fs_data, nullptr);
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


void Shader::load(const GLchar* vs_file_path, const GLchar* fs_file_path) { 
    vs_file_path_ = vs_file_path;
    fs_file_path_ = fs_file_path;

    string vs_code;
    string fs_code;

    try {
        ifstream vs_file(vs_file_path);
        ifstream fs_file(fs_file_path);

        stringstream vs_sstream, fs_sstream;
        vs_sstream << vs_file.rdbuf();
        fs_sstream << fs_file.rdbuf();

        vs_file.close();
        fs_file.close();

        vs_code = vs_sstream.str();
        fs_code = fs_sstream.str();

    } catch (exception e) {
        cerr << "SHADER FILES FAILED TO LOAD" << endl;
        throw;
    }

    compile(vs_code.c_str(), fs_code.c_str());

}



void Shader::use() {
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

