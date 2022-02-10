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
        // Clear screen
        // TODO: Use skybox instead
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // Show mouse cursor

        // glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        // glBindTexture(GL_TEXTURE_2D, m_loadedTextures[0]->id());

        // glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
        // glBindTexture(GL_TEXTURE_2D, m_loadedTextures[1]->id());

        // _shader->use();
        // _shader->setValue("texture1", 0);
        // _shader->setValue("texture2", 1);

        
        // // float rotation = sin(time * 2) * -45.0f;
        // // cubeRotation[i]
        // float scale = 1.0f + 0.25f + sin(2 * M_PI * 0.25f * time) * 0.25f;
        
        // // glm::mat4 transform = glm::mat4(1.0f);
        // // transform = glm::translate(transform, glm::vec3(0.2f, 0.2f, 0.0f));
        // // transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        // // transform = glm::scale(transform, glm::vec3(scale));
        
        // // m_shader->setValue("transform", transform);

        // float blend = 0.5f * (1.0f + sin(2 * M_PI * 0.5f * time));
        // _shader->setValue("blending", blend);

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

        // Unbind to not accidently continue writing to them
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::endRender() {
        // Display content from buffer
        glfwSwapBuffers(_window);
}

#endif