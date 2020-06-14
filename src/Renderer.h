#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class Renderer
{
public:
    void Draw(const VertexArray &vertices, const IndexBuffer &vertexIndices, const ShaderProgram &shader)const;
    void Clear()const;
};


struct SourceCode {
    std::string m_vertexShader;
    std::string m_fragmentShader;
};


void APIENTRY LogError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

SourceCode ParseShaderSourceCode(const std::string &filePath);


GLuint CompileShader(GLenum shaderType, const std::string &shaderSourceCode);

GLuint CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
