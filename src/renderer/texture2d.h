#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class Texture2d
	{
	public:
		explicit Texture2d(const GLuint width, const GLuint height, const unsigned char* data, 
						   const unsigned int channels = 4, 
						   const GLenum filter = GL_LINEAR, 
						   const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		Texture2d(Texture2d&& texture2d) noexcept;
		Texture2d& operator=(Texture2d&& texture2d) noexcept;
		~Texture2d();

		void bind() const;

		Texture2d() = delete;
		Texture2d(const Texture2d&) = delete;
		Texture2d& operator=(const Texture2d&) = delete;

	private:
		GLuint id;
		GLenum format;
		unsigned int width;
		unsigned int height;

	};
}