#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "windowmgr.h"

WindowMgr::~WindowMgr() {
    glfwTerminate();
}

GLFWwindow* WindowMgr::createWindow(int width, int height, const char* title) {
    GLFWwindow* wnd = _window;
    
    if (wnd != nullptr) {
        throw std::runtime_error("ERROR: Only one window allowed");
    }

    wnd = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwSetWindowSizeCallback(wnd, WindowMgr::window_resize_callback);

    if (wnd == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to instantiate GLFW window");
    }

    glfwMakeContextCurrent(wnd);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    return wnd;
}

void WindowMgr::window_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}