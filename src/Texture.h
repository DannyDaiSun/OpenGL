#pragma once
#include <string>
#include "GL/glew.h"

class Texture {
private:
	GLuint m_textureID=0;
	std::string m_filePath;
	unsigned char *m_localBuffer=nullptr;
	int m_width=0,m_height=0,m_bPP=0;
public:
	Texture(const std::string &filePath);

	~Texture();


	void Bind(unsigned int slot = 0)const;
	void Unbind()const;
	int GetWidth() const { return m_width; }
	int getHeight()const { return m_height; }
};

