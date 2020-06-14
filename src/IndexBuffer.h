#pragma once
#include "GL/glew.h"

class IndexBuffer{
private:
	GLuint m_bufferID=0;
	GLint m_count;
public:
	IndexBuffer(const GLuint *data, GLint count);
	~IndexBuffer();
	void Bind()const;
	void Unbind()const;
	GLint Count() const {
		return m_count;
	}
};

