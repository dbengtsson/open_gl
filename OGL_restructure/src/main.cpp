
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>
#include <string>

#include "utils.h"
#include "render/shader.h"
#include "render/model.h"
#include "scene/camera.h"

const uint32_t WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

GLFWwindow* window = nullptr;
Shader objectShader;

Camera cam = Camera(45.0f, (float)(WINDOW_WIDTH / WINDOW_HEIGHT), glm::vec3(0.5f, 0.0f, 8.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  2.0f),
	glm::vec3( 2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3( 0.0f,  0.0f, -3.0f)
};

Model model;

// Mouse input, move to viewport class or something
float lastX = 400, lastY = 300;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    float yaw = cam.getYaw() + xoffset;
    float pitch = cam.getPitch() + yoffset;
    cam.setYaw(yaw);
    cam.setPitch(pitch);
    
    if(pitch > 89.0f)
        cam.setPitch(89.0f);
    if(pitch < -89.0f)
        cam.setPitch(-89.0f);

    cam.updateCamera();
}

bool isAlive() { return !glfwWindowShouldClose(window); }
void closeApplication() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

void calcDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;
}

float fps() { return 1.0f / deltaTime; }

void createWindow(uint32_t w, uint32_t h, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, true);
    glfwSetCursorPosCallback(window, mouse_callback);
}

void initGL(uint32_t w, uint32_t h) {
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initScene() {
    objectShader = Shader("model_shader.vert", "model_shader.frag");
    model = Model("res/backpack/backpack.obj");
}

void processInputs() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        closeApplication();
    }

    if(glfwGetKey(window, GLFW_KEY_I)) {
        std::cout << "FPS: " << fps() << std::endl;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W)) {
        glm::vec3 offset = cam.getDirection() * cam.getMovementSpeed() * deltaTime;
        cam.setPosition(cam.getPosition() - offset);
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        glm::vec3 offset = glm::normalize(glm::cross(cam.getDirection(), cam.getUp())) * cam.getMovementSpeed() * deltaTime;
        cam.setPosition(cam.getPosition() + offset);
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        glm::vec3 offset = cam.getDirection() * cam.getMovementSpeed() * deltaTime;
        cam.setPosition(cam.getPosition() + offset);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        glm::vec3 offset = glm::normalize(glm::cross(cam.getDirection(), cam.getUp())) * cam.getMovementSpeed() * deltaTime;
        cam.setPosition(cam.getPosition() - offset);
    }
}

void render() {
    float time = glfwGetTime();
    objectShader.use();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = cam.getProjectionMatrix();
    glm::mat4 view = cam.getViewMatrix();

    objectShader.setUniform("projection", projection);
    objectShader.setUniform("view", view);

    // Licht und farben
    // objectShader.setUniform("viewPosition", cam.getPosition());
    // objectShader.setUniform("material.diffuseMap", 0); // 0 = assign TEXTURE_0
    // objectShader.setUniform("material.specularMap", 1);
    // objectShader.setUniform("material.shininess", 16.0f);

    // // objectShader.setUniform("light.position", lightPosition);
    // objectShader.setUniform("directionalLight.direction",   -0.2f, -1.0f, -0.3f);
    // objectShader.setUniform("directionalLight.ambient",      0.2f,  0.2f,  0.2f);
    // objectShader.setUniform("directionalLight.diffuse",      0.5f,  0.5f,  0.5f);
    // objectShader.setUniform("directionalLight.specular",     1.0f,  1.0f,  1.0f);

    // for (int i = 0; i < 4; i++) {
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].position",  pointLightPositions[i]);
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].ambient",   0.2f, 0.2f, 0.5f);
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].diffuse",   0.5f, 0.5f, 0.8f);
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].specular",  1.0f, 1.0f, 1.0f);
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].constant",  1.0f);
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].linear",    0.07f);
    //     objectShader.setUniform("pointLights[" + std::to_string(i) + "].quadratic", 0.017f);
    // }

    glm::mat4 m = glm::mat4(1.0f);
    m = glm::translate(m, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    m = glm::scale(m, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    objectShader.setUniform("model", m);
    model.draw(objectShader);

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, diffuseMap.getId());
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, specularMap.getId());

    // for (int i = 0; i < CUBE_COUNT; i++) {
    //     float angle = 65.0f;
    //     glm::mat4 model = glm::mat4(1.0f);
    //     model = glm::translate(model, pos[i]);
    //     model = glm::rotate(model, glm::radians(time * 100.0f), rot[i]);
    //     objectShader.setUniform("model", model);
    //     glDrawArrays(GL_TRIANGLES, 0, 36);
    // }

    // Draw light sources
    // glBindVertexArray(lightVAO);
    // lightShader.use();
    // lightShader.setUniform("projection", projection);
    // lightShader.setUniform("view", view);
    // for (int i = 0; i < 4; i++) {
    //     glm::mat4 pointLight = glm::mat4(1.0f);
    //     pointLight = glm::translate(pointLight, pointLightPositions[i]);
    //     pointLight = glm::scale(pointLight, glm::vec3(0.05f));
    //     lightShader.setUniform("model", pointLight);
    //     glDrawArrays(GL_TRIANGLES, 0, 36);
    // }

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
    initScene();
    while(isAlive()) { loop(); }

    return 0;
}

