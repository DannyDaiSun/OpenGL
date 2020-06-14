#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
class ShaderProgram {
private:
	std::unordered_map<std::string, GLint> m_uniformLocationCaches;
	std::string m_filePath;
	GLuint m_shaderProgramName=0;
public:
	ShaderProgram(const std::string &filePath);
	~ShaderProgram();

	void Bind()const;
	void Unbind()const;
	void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
private:
	GLint GetUniformLocation(const std::string &name);
};

