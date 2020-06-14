#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, GLsizeiptr size){
	glGenBuffers(1,&m_bufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size,data,GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
	glDeleteBuffers(1,&m_bufferID);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER,m_bufferID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
