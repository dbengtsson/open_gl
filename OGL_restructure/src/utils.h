#ifndef UTILS_H
#define UTILS_H
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string loadShaderCode(const char* filepath) {
    std::ifstream file;
    std::string sourceCode;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filepath);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        sourceCode = stream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return sourceCode;
}

// const glm::vec3 cubePositions[7][2] = {
//     { glm::vec3( 0.0f, -1.2f, 0.0f),      glm::vec3(1.0f, 0.5f, 0.2f) },
//     { glm::vec3( 1.2f,  0.0f, 0.0f),      glm::vec3(1.0f, 0.5f, 0.2f)},
//     { glm::vec3( 2.4f,  2.4f, 0.0f),    glm::vec3(1.0f, 0.5f, 0.2f) },
//     { glm::vec3( 3.6f,  1.2f, 0.0f),     glm::vec3(1.0f, 0.5f, 0.2f) },
//     { glm::vec3(-1.2f,  3.6f, 0.0f),     glm::vec3(1.0f, 0.5f, 0.2f) },
//     { glm::vec3(-2.4f,  0.0f, 0.0f),    glm::vec3(1.0f, 0.5f, 0.2f) },
//     { glm::vec3(-3.6f, -3.6f, 0.0f),    glm::vec3(1.0f, 0.5f, 0.2f) }
// };

const float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

// float vertices[] = {
//         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//          0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//          0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

//         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//          0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

//         -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//         -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

//          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//          0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

//         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//          0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//          0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

//         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//          0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//          0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//     };

static std::string GLenumToString(GLenum e) {
    switch(e) {
        case GL_VERTEX_SHADER:        return "VERTEX_SHADER";
        case GL_FRAGMENT_SHADER:      return "FRAGMENT_SHADER";
        default:                      return nullptr;
    }
}

#endif
    // // 2. compile shaders
    // unsigned int vertex, fragment;
    // int success;
    // char infoLog[512];
    
    // // vertex Shader
    // vertex = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertex, 1, &vShaderCode, NULL);
    // glCompileShader(vertex);
    // // print compile errors if any
    // glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    // if(!success)
    // {
    //     glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    // };

    // // Fragment Shader
    // fragment = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragment, 1, &fShaderCode, NULL);
    // glCompileShader(fragment);
    // // print compile errors if any
    // glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    // if(!success)
    // {
    //     glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    // };
    
    // // shader Program
    // _id = glCreateProgram();
    // glAttachShader(_id, vertex);
    // glAttachShader(_id, fragment);
    // glLinkProgram(_id);
    // // print linking errors if any
    // glGetProgramiv(_id, GL_LINK_STATUS, &success);

    // if(!success)
    // {
    //     glGetProgramInfoLog(_id, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    // }
    
    // // delete the shaders as they're linked into our program now and no longer necessary
    // glDeleteShader(vertex);
    // glDeleteShader(fragment);
