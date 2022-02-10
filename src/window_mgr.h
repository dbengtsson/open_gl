#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

#include <GLFW/glfw3.h>

class WindowMgr {
private:
    GLFWwindow* _window = nullptr;

    WindowMgr() {}
    
    static void window_resize_callback(GLFWwindow* window, int width, int height);
public:
    ~WindowMgr();

    GLFWwindow* createWindow(int width, int height, const char* title);

    GLFWwindow* window() { return _window; }

    static auto& instance() {
        static WindowMgr window;
        return window;
    }
};

#endif