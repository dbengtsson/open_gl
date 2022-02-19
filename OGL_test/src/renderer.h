#ifndef RENDERER_H
#define RENDERER_H
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Renderer {
private:
    GLFWwindow* _window;
public:
    Renderer(GLFWwindow* window);
    void beginRender();
    void endRender();
};

Renderer::Renderer(GLFWwindow* window) {
    _window = window;
}

void Renderer::beginRender() {
        // Enable z-buffer
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Clear screen
        // TODO: Use skybox instead
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Unbind to not accidently continue writing to them
        // glBindVertexArray(0);
        // glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::endRender() {
        // Display content from buffer
        glfwSwapBuffers(_window);
}

#endif