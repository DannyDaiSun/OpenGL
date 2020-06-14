#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1,&m_vertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1,&m_vertexArrayID);
}

void VertexArray::AddBuffer(const VertexBuffer &buffer, const VertexBufferLayout &layout)
{
	Bind();
	buffer.Bind();
	
	int attributeOffset=0;
	for (auto &attribute : layout.GetAttributes()) {
		glEnableVertexAttribArray(m_attributeIndex);
		glVertexAttribPointer(m_attributeIndex,attribute.m_count,
			attribute.m_type,attribute.m_normalized,layout.AttributesSizeInBytes(), (GLvoid*)attributeOffset);
		attributeOffset += attribute.m_count * layout.GetSizeInBytes(attribute.m_type);
		++m_attributeIndex;
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
