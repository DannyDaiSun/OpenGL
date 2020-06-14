#pragma once
#include <vector>
#include "GL/glew.h"
//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),0);
struct Attribute {
	GLint m_count;
	GLenum m_type;
	GLboolean m_normalized;
};

class VertexBufferLayout{
private:
	std::vector<Attribute> m_attributes;

	GLsizei m_attributesSize=0;



public:
	template <GLenum Type>
	void Push(GLint count);

	template<>
	void Push<GL_FLOAT>(GLint count) {
		m_attributes.push_back({count,GL_FLOAT,GL_FALSE});
		m_attributesSize+= GetSizeInBytes(GL_FLOAT)*count;
	}

	template<>
	void Push<GL_UNSIGNED_INT>(GLint count) {
		m_attributes.push_back({ count,GL_UNSIGNED_INT,GL_FALSE });
		m_attributesSize += GetSizeInBytes(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<GL_UNSIGNED_BYTE>(GLint count) {
		m_attributes.push_back({ count,GL_UNSIGNED_BYTE,GL_TRUE });
		m_attributesSize += GetSizeInBytes(GL_UNSIGNED_BYTE) * count;
	}

	const std::vector<Attribute> &GetAttributes() const{
		return m_attributes;
	}

	GLsizei AttributesSizeInBytes() const {
		return m_attributesSize;
	}

	const GLsizei GetSizeInBytes(GLenum type) const {
		switch (type) {
		case GL_FLOAT:
			return sizeof(float);
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
		case GL_UNSIGNED_BYTE:
			return sizeof(unsigned char);
		default:
			throw "Type Size Not Considered";
			break;
		}
	}
};

