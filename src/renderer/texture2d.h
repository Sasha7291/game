#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <map>
#include <string>

namespace Renderer
{
	class Texture2d
	{
	public:

		struct SubTexture2d
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			SubTexture2d(const glm::vec2& lbUV, const glm::vec2& rtUV) : leftBottomUV(lbUV), rightTopUV(rtUV) {}
			SubTexture2d() : leftBottomUV(0.0f), rightTopUV(1.0f) {}
		};

		explicit Texture2d(const GLuint width, 
						   const GLuint height, 
						   const unsigned char* data, 
						   const unsigned int channels = 4, 
						   const GLenum filter = GL_LINEAR, 
						   const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		Texture2d(Texture2d&& texture2d) noexcept;
		~Texture2d();

		void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		void bind() const;
		const unsigned int getHeight() const;
		const SubTexture2d& getSubTexture(const std::string& name) const;
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

		std::map<std::string, SubTexture2d> subTextures;

	};
}