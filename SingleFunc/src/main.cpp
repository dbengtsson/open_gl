
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include "utils.h"

const uint32_t WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
GLFWwindow* window = nullptr;
float lastUpdateTime = 0.0f;
float deltaTime = 0.0f;
uint32_t VAO, VBO;
uint32_t shaderProgram;

void createWindow(uint32_t w, uint32_t h, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

void initGL(uint32_t w, uint32_t h) {
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.776f, 0.168f, 0.411f, 1.0f);
}

void createVAO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeWithNormals), cubeWithNormals, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
}

void createObjectShader() {
    int success;
    char log[512];

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vString = loadShaderCode("basic_shader.vert");
    const char* vSrc = vString.c_str();
    glShaderSource(vShader, 1, &vSrc, NULL);
    glCompileShader(vShader);
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vShader, 512, NULL, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    };

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fString = loadShaderCode("basic_shader.frag");
    const char* fSrc = fString.c_str();
    glShaderSource(fShader, 1, &fSrc, NULL);
    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fShader, 512, NULL, log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
    };

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    glUseProgram(shaderProgram);
}

bool isAlive() { return !glfwWindowShouldClose(window); }
void closeApplication() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

void calcDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;
}

float fps() { return 1.0f / deltaTime; }

void processInputs() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        closeApplication();
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    float rotation = glfwGetTime() * 100.0f;
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation * 0.5f), glm::vec3(1.0f, 0.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(rotateX), glm::vec3(0.0f, 1.0f, 0.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glfwSwapBuffers(window);
}

void loop() {
    calcDeltaTime();
    processInputs();
    render();
    glfwPollEvents();
    // std::cout << fps() << std::endl;
}

int main() {
    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mitt fönster");
    initGL(WINDOW_WIDTH, WINDOW_HEIGHT);
    createVAO();
    createObjectShader();
    while(isAlive()) { loop(); }

    return 0;
}

