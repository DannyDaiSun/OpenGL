#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
Texture::Texture(const std::string &filePath): m_filePath(filePath){
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bPP, 4);

	glGenTextures(1, &m_textureID);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);

	if (m_localBuffer) {
		stbi_image_free(m_localBuffer);
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &m_textureID);
}

void Texture::Bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
