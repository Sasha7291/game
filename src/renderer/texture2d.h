#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <map>
#include <string>

namespace RenderEngine
{
	class Texture2d
	{
	public:
		explicit Texture2d::Texture2d(const unsigned char* data,
									  const unsigned int channels,
									  const GLuint width,
									  const GLuint height,
								 	  const GLenum filter,
									  const GLenum wrapMode);
		Texture2d(Texture2d&& texture2d) noexcept;
		~Texture2d();
		
		void bind() const;
		const unsigned int getHeight() const;
		const unsigned int getWidth() const;

		Texture2d& operator=(Texture2d&& texture2d) noexcept;

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