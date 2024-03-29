#include "texture2d.h"

namespace RenderEngine 
{
	Texture2d::Texture2d(const unsigned char* data,
						 const unsigned int channels,
						 const GLuint width,
						 const GLuint height,
						 const GLenum filter, 
						 const GLenum wrapMode) 
		: id(0)
		, width(width)
		, height(height)
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

	Texture2d::Texture2d(Texture2d&& texture2d) noexcept
	{
		id = texture2d.id;
		format = texture2d.format;
		height = texture2d.height;
		width = texture2d.width;

		texture2d.id = 0;
		texture2d.format = 0;
		texture2d.height = 0;
		texture2d.width = 0;
	}

	Texture2d::~Texture2d()
	{
		glDeleteTextures(1, &id);
	}

	void Texture2d::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	const unsigned int Texture2d::getHeight() const
	{
		return height;
	}

	const unsigned int Texture2d::getWidth() const
	{
		return width;
	}

	Texture2d& Texture2d::operator=(Texture2d&& texture2d) noexcept
	{
		glDeleteTextures(1, &id);

		id = texture2d.id;
		format = texture2d.format;
		height = texture2d.height;
		width = texture2d.width;

		texture2d.id = 0;
		texture2d.format = 0;
		texture2d.height = 0;
		texture2d.width = 0;

		return *this;
	}
}

