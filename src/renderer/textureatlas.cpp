#include "textureatlas.h"

namespace RenderEngine
{
	TextureAtlas::TextureAtlas(const unsigned char* data, 
							   const unsigned int channels, 
							   const GLuint width, 
							   const GLuint height, 
							   const GLenum filter, 
							   const GLenum wrapMode)
		: Texture2d(data, channels, width, height, filter, wrapMode)
	{}

	void TextureAtlas::addSubTexture(const std::string& name,
									 const glm::vec2& leftBottomUV, 
									 const glm::vec2& rightTopUV)
	{
		subTextures.emplace(name, SubTexture2d(leftBottomUV, rightTopUV));
	}

	const TextureAtlas::SubTexture2d& TextureAtlas::getSubTexture(const std::string& name) const
	{
		auto it = subTextures.find(name);

		if (it == subTextures.end())
		{
			const static SubTexture2d defaultSubTexture;
			return defaultSubTexture;
		}

		return it->second;
	}
}