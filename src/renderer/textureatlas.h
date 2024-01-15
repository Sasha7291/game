#pragma once

#include "texture2d.h"

namespace RenderEngine
{
	class TextureAtlas : public Texture2d
	{
	public:
		struct SubTexture2d
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			explicit SubTexture2d(const glm::vec2& lbUV, const glm::vec2& rtUV)
				: leftBottomUV(lbUV)
				, rightTopUV(rtUV)
			{}
			SubTexture2d()
				: leftBottomUV(0.0f)
				, rightTopUV(1.0f)
			{}
		};

		explicit TextureAtlas(const unsigned char* data,
							  const unsigned int channels,
							  const GLuint width,
							  const GLuint height,
							  const GLenum filter,
							  const GLenum wrapMode);

		void addSubTexture(const std::string& name,
						   const glm::vec2& leftBottomUV,
						   const glm::vec2& rightTopUV);
		const SubTexture2d& getSubTexture(const std::string& name) const;

	private:
		std::map<std::string, SubTexture2d> subTextures;

	};
}