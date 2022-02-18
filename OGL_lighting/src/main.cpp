
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include "utils.h"
#include "render/shader.h"

const uint32_t WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
GLFWwindow* window = nullptr;
uint32_t VAO, VBO;
Shader objectShader;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);

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
}

void createVAO() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeWithNormals), cubeWithNormals, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void initShaders() {
    objectShader = Shader("basic_shader.vert", "basic_shader.frag");
}

bool isAlive() { return !glfwWindowShouldClose(window); }
void closeApplication() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

void calcDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;
}

float fps() { return 1.0f / deltaTime; }
void processInputs() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        closeApplication();
    }

    if(glfwGetKey(window, GLFW_KEY_I)) {
        std::cout << "FPS: " << fps() << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_W)) {
        lightPosition.y +=1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        lightPosition.x -=1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        lightPosition.y -=1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        lightPosition.x +=1.0f;
    }
}

void render() {
    float time = glfwGetTime();
    objectShader.use();

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);
    objectShader.setUniform("projection", proj);

    glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, -5.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, viewPos);
    objectShader.setUniform("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(time * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(time * 50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    objectShader.setUniform("model", model);

    // Licht und farben
    // objectShader.setUniform("material.ambient", 1.0f, 0.5f, 0.31f);
    objectShader.setUniform("material.diffuse", 1.0f, 0.5f, 0.31f);
    objectShader.setUniform("material.specular", 0.5f, 0.5f, 0.5f);
    // objectShader.setUniform("material.ambient", 0.05f, 0.0f, 0.0f);
    // objectShader.setUniform("material.diffuse", 0.5f, 0.4f, 0.4f);
    // objectShader.setUniform("material.specular", 0.7f, 0.04f, 0.04f);
    objectShader.setUniform("material.shininess", 8.0f); 

    glm::vec3 lightColor = glm::vec3(sin(time * 2.0f), sin(time * 0.7f), sin(time * 1.3f));
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    glm::vec3 specularColor = glm::vec3(1.0f);
    
    objectShader.setUniform("light.position", lightPosition);
    objectShader.setUniform("light.ambient", ambientColor);
    objectShader.setUniform("light.diffuse", diffuseColor);
    objectShader.setUniform("light.specular", specularColor);

    // Draw
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glfwSwapBuffers(window);
}

void loop() {
    calcDeltaTime();
    processInputs();
    render();
    glfwPollEvents();
}

int main() {
    createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mitt fönster");
    initGL(WINDOW_WIDTH, WINDOW_HEIGHT);
    createVAO();
    initShaders();
    while(isAlive()) { loop(); }

    return 0;
}

