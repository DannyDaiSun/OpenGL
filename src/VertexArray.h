#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
class VertexArray{
private:
	GLuint m_vertexArrayID=0;
	GLuint m_attributeIndex=0;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout);

	void Bind()const;
	void Unbind()const;
};

