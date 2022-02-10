#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "windowmgr.h"
#include "shader.h"
#include "texture.h"
#include "image.h"

const uint32_t WINDOW_WIDTH = 1366;
const uint32_t WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Världens bästa spel";
const char* VERTEX_SHADER_FILEPATH = "hlsl/shader.vert";
const char* FRAGMENT_SHADER_FILEPATH = "hlsl/shader.frag";
const char* TEXTURE0_FILEPATH = "res/karingo.tga";
const char* TEXTURE1_FILEPATH = "res/hunt.tga";

const unsigned int OBJECT_COUNT = 1000;
const float OBJECT_SPREAD = 100.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Application {
private:
    // GLFWwindow* window;
    GLFWwindow* _window;
    uint32_t vertexBufferObject, vertexArrayObject, EBO;
    Shader *_shader;

    glm::vec3 cubePositions[OBJECT_COUNT];
    float cubeRotation[OBJECT_COUNT];

    // TEST
    Texture *m_loadedTextures[3];

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
    GLFWcursor* cursor;
    glm::vec2 mousePosition = glm::vec2(-1.0f);

    void init() {
        // Initialize GLFW lib
        glfwInit();
        // Set OpenGL version to target
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create target window
        _window = WindowMgr::instance().createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

        _shader = new Shader(VERTEX_SHADER_FILEPATH, FRAGMENT_SHADER_FILEPATH);

        glGenVertexArrays(1, &vertexArrayObject);
        glGenBuffers(1, &vertexBufferObject);
        glGenBuffers(1, &EBO);

        glBindVertexArray(vertexArrayObject);

        // float vertices[] = {
        //     // positions          // colors           // texture coords
        //      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        //      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        //     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        // };

        // Enable mouse input
        // createCursor();
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // glfwSetCursor(window, cursor);
        // glfwSetCursorPosCallback(window, static_mouse_callback);


        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        std::default_random_engine r;
        std::uniform_real_distribution<float> posRand(-OBJECT_SPREAD, OBJECT_SPREAD);
        // std::uniform_real_distribution<float> posZ(-1, 1);
        std::uniform_real_distribution<float> rot(0, 360);

        for (unsigned int i = 0; i < OBJECT_COUNT; i++) {
            float x, y, z;
            x = posRand(r);
            y = posRand(r);
            z = posRand(r);

            cubePositions[i] = glm::vec3(x, y, z);
            cubeRotation[i] = rot(r);
        }

        // unsigned int indices[] = {  // note that we start from 0!
        //     0, 1, 3,   // first triangle
        //     1, 2, 3    // second triangle
        // };  

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // // For indices
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Vertex positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // // For using vertex colors in vertex array
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        // glEnableVertexAttribArray(1);
        
        // Texture coordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Test stuff
        m_loadedTextures[0] = new Texture(TEXTURE0_FILEPATH);
        m_loadedTextures[1] = new Texture(TEXTURE1_FILEPATH);
    }

    // void createCursor() {
    //     Image img("res/mouse_cursor.tga");
        
    //     GLFWimage image;
    //     image.width = img.getWidth();
    //     image.height = img.getHeight();
    //     image.pixels = img.getData();
        
    //     cursor = glfwCreateCursor(&image, 0, 0);
    // }

    // // void initWindow() {
    // //     glfwInit();
    // //     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // //     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // //     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // //     window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    // //     if (window == nullptr) {
    // //         glfwTerminate();
    // //         throw std::runtime_error("Failed to instantiate GLFW window");
    // //     }

    // //     glfwMakeContextCurrent(window);
    // //     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    // //         throw std::runtime_error("Failed to initialize GLAD");
    // //     }

    // //     glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // // }

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

        

        glEnable(GL_DEPTH_TEST); // Enable z-buffer

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Show mouse cursor

        glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, m_loadedTextures[0]->id());

        glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, m_loadedTextures[1]->id());

        _shader->use();
        _shader->setValue("texture1", 0);
        _shader->setValue("texture2", 1);

        
        // float rotation = sin(time * 2) * -45.0f;
        // cubeRotation[i]
        float scale = 1.0f + 0.25f + sin(2 * M_PI * 0.25f * time) * 0.25f;
        
        // glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::translate(transform, glm::vec3(0.2f, 0.2f, 0.0f));
        // transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        // transform = glm::scale(transform, glm::vec3(scale));
        
        // m_shader->setValue("transform", transform);

        float blend = 0.5f * (1.0f + sin(2 * M_PI * 0.5f * time));
        _shader->setValue("blending", blend);

        // Camera
        // // Spinning camera
        // float radius = 10.0f;
        // float camX = sin(time) * radius;
        // float camZ = cos(time) * radius;
        // glm::vec3 cameraPosition = glm::vec3(camX, 0.0f, camZ);

        // Default camera
        // glm::vec3 cameraPosition = glm::vec3(6.0f, 2.0f, 4.0f);
        // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        // glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
        // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraPosition));
        // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

        // View Matrix
        glm::mat4 view = glm::mat4(1.0f);
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
        // Non free-look camera
        // view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        _shader->setViewMatrix(view);

        // Projection Matrix
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 10000.0f);
        _shader->setProjectionMatrix(projection);

        glBindVertexArray(vertexArrayObject);
        // // single box
        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f));
        // m_shader->setModelMatrix(model);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glm::mat4 model;

        for (unsigned int i = 0; i < OBJECT_COUNT; i++) {
            // translate all defined vertices in global space
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            // model = glm::translate(model, glm::vec3(0.0f, 0.0f, -100.0f));
            float rotation = time * cubeRotation[i];
            // model = glm::rotate(model, glm::radians(time * 50), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.5f, 0.0f));
            _shader->setModelMatrix(model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Mouse, hide initially until we get movement.
        // if (mousePosition.x > -1.0f && mousePosition.y > -1.0f) {
        //     model = glm::mat4(1.0f);
        //     model = glm::translate(model, glm::vec3(mousePosition.x, mousePosition.y, 1.0f));
        //     model = glm::scale(model, glm::vec3(100.0f));
        //     m_shader->setModelMatrix(model);
        //     view = glm::mat4(1.0f);
        //     m_shader->setViewMatrix(view);
        //     projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        //     m_shader->setProjectionMatrix(projection);
        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

        // // For using indices
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glfwSwapBuffers(window);
    }

    void mainLoop(GLFWwindow *window) {
        while(!glfwWindowShouldClose(window)) {
            processInput(window);
            render(window);
            glfwPollEvents();
        }
    }

    void cleanup() {
        delete _shader;
        unsigned int arr_size = sizeof(m_loadedTextures)/sizeof(m_loadedTextures[0]);
        for(int i = 0; i < arr_size; i++) {
            delete m_loadedTextures[i]; // delete the objects in the array also, who cares rn
        }
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