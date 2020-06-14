#include <iostream>


#include "ShaderProgram.h"
#include "Renderer.h"

ShaderProgram::ShaderProgram(const std::string &filePath):m_filePath(filePath){
    SourceCode s = ParseShaderSourceCode(filePath);
    m_shaderProgramName = CreateShader(s.m_vertexShader, s.m_fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_shaderProgramName);
}

void ShaderProgram::Bind() const {
    glUseProgram(m_shaderProgramName);
}

void ShaderProgram::Unbind() const {
    glUseProgram(0);
}

void ShaderProgram::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    Bind();
    GLint glLocation = GetUniformLocation(name);
    glUniform4f(glLocation, v0, v1, v2, v3);
}

GLint ShaderProgram::GetUniformLocation(const std::string &name) {
    if (m_uniformLocationCaches.find(name) != m_uniformLocationCaches.end()) {
        return m_uniformLocationCaches[name];
    }

    GLint glLocation = glGetUniformLocation(m_shaderProgramName, name.c_str());

    if (glLocation == -1) {
        std::cout << "Uniform Name: "<< name<<" doesn't Exist or Inactive" << std::endl;
    }
    
    m_uniformLocationCaches.emplace(name, glLocation);

    return glLocation;
}
