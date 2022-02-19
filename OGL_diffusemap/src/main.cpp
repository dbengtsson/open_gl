
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
#include "scene/camera.h"

const uint32_t WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
GLFWwindow* window = nullptr;
uint32_t objectVAO, lightVAO, VBO;
Shader objectShader, lightShader;
Texture texture;

Camera cam = Camera(45.0f, (float)(WINDOW_WIDTH / WINDOW_HEIGHT));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 10.0f);

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
    glGenVertexArrays(1, &objectVAO);
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(objectVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void initShaders() {
    objectShader = Shader("basic_shader.vert", "basic_shader.frag");
    lightShader = Shader("light_shader.vert", "light_shader.frag");
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
        glm::vec3 offset = (glm::vec3(0.0f, 0.0f, -1.0f) * cam.getMovementSpeed() * deltaTime);
        cam.setPosition(offset + cam.getPosition());
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        glm::vec3 offset = (glm::vec3(-1.0f, 0.0f, 0.0f) * cam.getMovementSpeed() * deltaTime);
        cam.setPosition(offset + cam.getPosition());
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        glm::vec3 offset = (glm::vec3(0.0f, 0.0f, 1.0f) * cam.getMovementSpeed() * deltaTime);
        cam.setPosition(offset + cam.getPosition());
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        glm::vec3 offset = (glm::vec3(1.0f, 0.0f, 0.0f) * cam.getMovementSpeed() * deltaTime);
        cam.setPosition(offset + cam.getPosition());
    }
}

void render() {
    float time = glfwGetTime();
    objectShader.use();
    glm::mat4 projection = cam.getProjectionMatrix();
    glm::mat4 view = cam.getViewMatrix();

    objectShader.setUniform("projection", projection);
    objectShader.setUniform("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    // model = glm::rotate(model, glm::radians(time * 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(time * 50.0f), glm::vec3(1.0f, 0.5f, 0.0f));
    // model = glm::rotate(model, glm::radians(45.0f), glm::vec3(-0.3f, 1.0f, 0.0f));
    objectShader.setUniform("model", model);

    // Licht und farben
    objectShader.setUniform("viewPosition", cam.getPosition());
    objectShader.setUniform("material.diffuse", 1.0f, 0.5f, 0.31f);
    objectShader.setUniform("material.specular", 0.5f, 0.5f, 0.5f);
    objectShader.setUniform("material.shininess", 32.0f); 

    glm::vec3 lightColor = glm::vec3(1.0f); // glm::vec3(sin(time * 2.0f), sin(time * 0.7f), sin(time * 1.3f));
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
    glBindVertexArray(objectVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    lightShader.use();
    lightShader.setUniform("projection", projection);
    lightShader.setUniform("view", view);
    glm::mat4 light = glm::mat4(1.0f);
    light = glm::translate(light, lightPosition);
    light = glm::scale(light, glm::vec3(0.2f));
    lightShader.setUniform("model", light);

    glBindVertexArray(lightVAO);
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

