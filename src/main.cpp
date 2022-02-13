#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"

#include "window_mgr.h"

#include "scenes/i_scene.h"
#include "scenes/test_scene.h"

#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "image.h"
#include "text.h"

class Application {
private:
    GLFWwindow* _window;
    IScene* _activeScene;
    Renderer* _renderer;
    Text* _text;
    // Deltatime
    float deltaTime = 0.0f;
    float lastUpdateTime = 0.0f;

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

        _text = new Text();
        _text->loadFont("res/fonts/source_code_pro.ttf");
        // Create test scene for rendering
        _activeScene = new TestScene();
    }

    void processInput(GLFWwindow* window) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        // Camera movement
        // const float cameraSpeed = 25.0f * deltaTime;
        // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //     cameraPosition += cameraSpeed * cameraFront;
        // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //     cameraPosition -= cameraSpeed * cameraFront;
        // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        //     cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        //     cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    void render(GLFWwindow *window) {
        float time = glfwGetTime();
        deltaTime = time - lastUpdateTime;
        lastUpdateTime = time;
        _renderer->beginRender();
        _activeScene->render();
        //_text->renderText("Test", 25.0f, 25.0f, 1.0f, glm::vec3(0.5f));
        _renderer->endRender();
        // if (glGetError()) {
        std::cout << "fps: " << 1.0f / deltaTime << std::endl;
        // }
    }

    void mainLoop(GLFWwindow *window) {
        while(!glfwWindowShouldClose(window)) {
            processInput(window);
            render(window);
            glfwPollEvents();
        }
    }

    void cleanup() {}

public:
    void run() {
        init();
        if (_window != nullptr) {
            mainLoop(_window);
        }
        cleanup();
    }
};

int main() {
    Application app;
    app.run();
    return 0;
}