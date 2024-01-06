#include "texture2d.h"

namespace Renderer 
{
	Texture2d::Texture2d(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int channels, const GLenum filter, const GLenum wrapMode) :
		id(0), width(width), height(height)
	{
		switch (channels)
		{
		case 3:
			format = GL_RGB;
			break;

		case 4:
		default:
			format = GL_RGBA;
			break;
		}

		glGenTextures(1, &id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2d::~Texture2d()
	{
		glDeleteTextures(1, &id);
	}

	Texture2d::Texture2d(Texture2d&& texture2d) noexcept
	{
		id = texture2d.id;
		format = texture2d.format;
		height = texture2d.height;
		width = texture2d.width;

		texture2d.id = 0;
	}

	Texture2d& Texture2d::operator=(Texture2d&& texture2d) noexcept
	{
		glDeleteTextures(1, &id);

		id = texture2d.id;
		format = texture2d.format;
		height = texture2d.height;
		width = texture2d.width;

		texture2d.id = 0;
		
		return *this;
	}

	void Texture2d::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
}

