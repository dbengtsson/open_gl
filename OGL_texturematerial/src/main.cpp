
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
#include "render/texture.h"

const uint32_t WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
GLFWwindow* window = nullptr;
uint32_t VAO, VBO;
Shader objectShader;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);

Texture tex;

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void initShaders() {
    objectShader = Shader("basic_shader.vert", "basic_shader.frag");
    tex = Texture("res/container2.png");
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
    objectShader.setUniform("viewPos", viewPos);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(time * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(time * 50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    objectShader.setUniform("model", model);

    // Licht und farben
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.getId());
    objectShader.setUniform("material.diffuse", 0);
    objectShader.setUniform("material.specular", 0.5f, 0.5f, 0.5f);
    objectShader.setUniform("material.shininess", 64.0f);

    objectShader.setUniform("light.position", lightPosition);
    objectShader.setUniform("light.ambient", 0.2f, 0.2f, 0.2f);
    objectShader.setUniform("light.diffuse", 0.5f, 0.5f, 0.5f);
    objectShader.setUniform("light.specular", 1.0f, 1.0f, 1.0f);

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

