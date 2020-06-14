#pragma once
#include <GL/glew.h>
class VertexBuffer {
private:
	
	GLuint m_bufferID=0;
public:
	VertexBuffer(const void *data, GLsizeiptr size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
};