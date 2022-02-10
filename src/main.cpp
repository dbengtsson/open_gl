#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window_mgr.h"

#include "scenes/i_scene.h"
#include "scenes/test_scene.h"

#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "image.h"

const uint32_t WINDOW_WIDTH = 1366;
const uint32_t WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Världens bästa spel";

const unsigned int OBJECT_COUNT = 1000;
const float OBJECT_SPREAD = 100.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Application {
private:
    GLFWwindow* _window;
    IScene* _activeScene;
    Renderer* _renderer;

    // Camera
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 4.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Deltatime
    float deltaTime = 0.0f;
    float lastUpdateTime = 0.0f;
    // glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraPosition));
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // GLFWcursor* cursor;
    // glm::vec2 mousePosition = glm::vec2(-1.0f);

    void init() {
        // Initialize GLFW lib
        glfwInit();
        // Set OpenGL version to target
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create target window
        _window = WindowMgr::instance().createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
        _renderer = new Renderer(_window);
        // Create test scene for rendering
        _activeScene = new TestScene();
    }

    void processInput(GLFWwindow* window) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        // Camera movement
        const float cameraSpeed = 25.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPosition += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPosition -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    void render(GLFWwindow *window) {
        float time = glfwGetTime();
        deltaTime = time - lastUpdateTime;
        lastUpdateTime = time;
        _renderer->beginRender();
        _activeScene->render();
        _renderer->endRender();

        // // Camera
        // // // Spinning camera
        // // float radius = 10.0f;
        // // float camX = sin(time) * radius;
        // // float camZ = cos(time) * radius;
        // // glm::vec3 cameraPosition = glm::vec3(camX, 0.0f, camZ);

        // // Default camera
        // // glm::vec3 cameraPosition = glm::vec3(6.0f, 2.0f, 4.0f);
        // // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        // // glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
        // // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        // // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraPosition));
        // // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

        // // View Matrix
        // glm::mat4 view = glm::mat4(1.0f);
        // // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
        // // Non free-look camera
        // // view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        // view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        // _shader->setViewMatrix(view);

        // // Projection Matrix
        // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 10000.0f);
        // _shader->setProjectionMatrix(projection);

        // glBindVertexArray(vertexArrayObject);
        // // // single box
        // // glm::mat4 model = glm::mat4(1.0f);
        // // model = glm::translate(model, glm::vec3(0.0f));
        // // m_shader->setModelMatrix(model);
        // // glDrawArrays(GL_TRIANGLES, 0, 36);
        // glm::mat4 model;

        // for (unsigned int i = 0; i < OBJECT_COUNT; i++) {
        //     // translate all defined vertices in global space
        //     model = glm::mat4(1.0f);
        //     model = glm::translate(model, cubePositions[i]);
        //     // model = glm::translate(model, glm::vec3(0.0f, 0.0f, -100.0f));
        //     float rotation = time * cubeRotation[i];
        //     // model = glm::rotate(model, glm::radians(time * 50), glm::vec3(0.0f, 1.0f, 0.0f));
        //     model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.5f, 0.0f));
        //     _shader->setModelMatrix(model);
        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

        // // Mouse, hide initially until we get movement.
        // // if (mousePosition.x > -1.0f && mousePosition.y > -1.0f) {
        // //     model = glm::mat4(1.0f);
        // //     model = glm::translate(model, glm::vec3(mousePosition.x, mousePosition.y, 1.0f));
        // //     model = glm::scale(model, glm::vec3(100.0f));
        // //     m_shader->setModelMatrix(model);
        // //     view = glm::mat4(1.0f);
        // //     m_shader->setViewMatrix(view);
        // //     projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        // //     m_shader->setProjectionMatrix(projection);
        // //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // // }

        // // // For using indices
        // // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0);
        // glBindTexture(GL_TEXTURE_2D, 0);
        
        // glfwSwapBuffers(window);
    }

    void mainLoop(GLFWwindow *window) {
        while(!glfwWindowShouldClose(window)) {
            processInput(window);
            render(window);
            glfwPollEvents();
        }
    }

    void cleanup() {
        // delete _activeScene;
    }

public:
    void run() {
        init();
        if (_window != nullptr) {
            mainLoop(_window);
        }
        cleanup();
    }

    // void actual_mouse_callback(GLFWwindow* window, double mouseX, double mouseY) {
    //     mousePosition = glm::vec2(mouseX, (float)WINDOW_HEIGHT - mouseY);
    // }

    // static void static_mouse_callback(GLFWwindow* window, double mouseX, double mouseY) {
    //     Application::getInstance().actual_mouse_callback(window, mouseX, mouseY);
    // }

    static Application& getInstance() // Singleton is accessed via getInstance()
    {
        static Application instance; // lazy singleton, instantiated on first use
        return instance;
    }
};

int main() {
    Application::getInstance().run();
    return 0;
}