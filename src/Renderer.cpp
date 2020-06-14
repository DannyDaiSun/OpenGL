#include "Renderer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void APIENTRY LogError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

    if (source == 33350 && type == 33361 && id == 131185 && severity == 33387) {
        //Ignore this error: Buffer detailed info: Buffer object 1 (...) will use video memory as the source for buffer object operations
        return;
    }

    std::cout << "------" << std::endl;
    std::cout << "[Source: " << source << ", " << "Type: " << type << ", ID: " << id << ", Severity: " << severity << "]" << std::endl;
    std::cout << "Error: " << message << std::endl;
    std::cout << "------" << std::endl;
}

SourceCode ParseShaderSourceCode(const std::string &filePath) {
    enum class ShaderType {
        None,
        Vertex,
        Fragment
    };

    ShaderType type = ShaderType::None;
    std::ostringstream ossVertex;
    std::ostringstream ossFragment;

    std::ifstream ifs(filePath);
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::Fragment;
            } else {
                std::cout << "Error in ParseShaderSourceCode(...)" << std::endl;
            }
        } else if (type != ShaderType::None) {
            if (type == ShaderType::Vertex) {
                ossVertex << line << '\n';
            } else if (type == ShaderType::Fragment) {
                ossFragment << line << '\n';
            }
        } else {
            std::cout << "Parsed line but don't know the shader type of sourceCode" << std::endl;
        }
    }


    return { ossVertex.str(),ossFragment.str() };
}


GLuint CompileShader(GLenum shaderType, const std::string &shaderSourceCode) {
    GLuint shaderName = glCreateShader(shaderType);
    const char *s = shaderSourceCode.c_str();
    glShaderSource(shaderName, 1, &s, NULL);
    glCompileShader(shaderName);
    GLint status;
    glGetShaderiv(shaderName, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &logLength);
        auto p = std::make_unique<char[]>(logLength);
        glGetShaderInfoLog(shaderName, logLength, NULL, p.get());
        std::cout << "Shader Compilation Failed" << std::endl;
        std::cout << p.get() << std::endl;
        glDeleteShader(shaderName);
        return 0;
    }
    return shaderName;
}

GLuint CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    GLuint vertexShaderName = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragmentShaderName = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShaderName);
    glAttachShader(program, fragmentShaderName);

    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vertexShaderName);
    glDeleteShader(fragmentShaderName);

    return program;
}

void Renderer::Draw(const VertexArray &vertices, const IndexBuffer &vertexIndices,
    const ShaderProgram &shader) const{
    vertices.Bind();
    vertexIndices.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, vertexIndices.Count(), GL_UNSIGNED_INT, NULL);
}

void Renderer::Clear()const {
    glClear(GL_COLOR_BUFFER_BIT);
}