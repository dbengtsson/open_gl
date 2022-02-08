#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
// TODO: Add serialization of shaders so it's not visible in distribution
class Shader {
private:
    unsigned int m_id;
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void use();
    void setValue(const std::string &name, bool value);
    void setValue(const std::string &name, float value);
    void setValue(const std::string &name, double value);
    void setValue(const std::string &name, int value);
    void setValue(const std::string &name, glm::mat4 value);

    void setProjectionMatrix(const glm::mat4& matrix);
    void setViewMatrix(const glm::mat4& matrix);
    void setModelMatrix(const glm::mat4& matrix);

    unsigned int id() { return m_id; }
};

#endif