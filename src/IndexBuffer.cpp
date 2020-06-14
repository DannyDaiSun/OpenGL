#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint *data, GLint count):m_count(count){
	glGenBuffers(1,&m_bufferID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_count * sizeof(GLuint),data,GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1,&m_bufferID);
}

void IndexBuffer::Bind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferID);
}

void IndexBuffer::Unbind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
