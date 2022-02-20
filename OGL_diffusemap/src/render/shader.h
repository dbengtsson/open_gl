#ifndef SHADER_H
#define SHADER_H
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../utils.h"

class Shader {
private:
    uint32_t m_program;

    uint32_t compileShader(const char* filepath, GLenum type) {
        std::ifstream file;
        std::string code;

        file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try {
            file.open(filepath);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            code = stream.str();
        }
        catch(std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        int success;
        char log[512];
        unsigned int shader = glCreateShader(type);
        const char* src = code.c_str();
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 512, NULL, log);
            std::cout << "ERROR::" << GLenumToString(type) << "::COMPILATION_FAILED\n" << log << std::endl;
        };

        return shader;
    }
public:
    Shader() {}
    Shader(const char* vsFilepath, const char* fsFilepath) {
        uint32_t vs = compileShader(vsFilepath, GL_VERTEX_SHADER);
        uint32_t fs = compileShader(fsFilepath, GL_FRAGMENT_SHADER);
        uint32_t program = glCreateProgram();

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);

        m_program = program;
    }

    void use() {
        glUseProgram(m_program);
    }

    // Matrix 4x4
    void setUniform(const char* name, const glm::mat4& value) {
        uint32_t uniformLocation = glGetUniformLocation(m_program, name);
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
    }

    // Vector 3
    void setUniform(const char* name, const glm::vec3& value) {
        uint32_t uniformLocation = glGetUniformLocation(m_program, name);
        glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
    }

    // 3 floats to vector
    void setUniform(const char* name, float x, float y, float z) {
        uint32_t uniformLocation = glGetUniformLocation(m_program, name);
        glUniform3f(uniformLocation, x, y, z);
    }

    // Single float value
    void setUniform(const char* name, float value) {
        uint32_t uniformLocation = glGetUniformLocation(m_program, name);
        glUniform1f(uniformLocation, value);
    }

    void setUniform(const char* name, int value) {
        uint32_t uniformLocation = glGetUniformLocation(m_program, name);
        glUniform1i(uniformLocation, value);
    }
};

#endif