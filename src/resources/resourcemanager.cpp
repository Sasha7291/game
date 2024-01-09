#include "resourcemanager.h"

#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::AnimatedSpriteMap ResourceManager::animatedSprites;
ResourceManager::ShaderProgramMap ResourceManager::shaderPrograms;
ResourceManager::SpriteMap ResourceManager::sprites;
ResourceManager::TextureMap ResourceManager::textures;
std::string ResourceManager::resPath;

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::loadAnimatedSprite(const std::string& spriteName, 
																			  const std::string& textureName, 
																			  const std::string& shaderName, 
																			  const unsigned int width, 
																			  const unsigned int height, 
																			  const std::string& subTextureName)
{
	auto texture = getTexture(textureName);
	if (texture == nullptr)
	{
		std::cerr << "ERROR::Texture " << textureName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto shaderProgram = getShaderProgram(shaderName);
	if (texture == nullptr)
	{
		std::cerr << "ERROR::Shader program " << shaderName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto& newAnimatedSprite = animatedSprites.emplace(spriteName, std::make_shared<Renderer::AnimatedSprite>(texture,
																											 subTextureName,
																											 shaderProgram,
																											 glm::vec2(0.0f, 0.0f),
																											 glm::vec2(width, height))).first->second;
	return newAnimatedSprite;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileText(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "ERROR::Vertex shader file is empty!" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileText(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "ERROR::Fragment shader file is empty!" << std::endl;
		return nullptr;
	}

	auto& newShader = shaderPrograms.emplace(name, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (!newShader->isCompiled())
	{
		std::cerr << "ERROR::Shader program wasn't loaded: \n" 
				  << "Vertex shader: " << vertexPath << "\n" 
				  << "Fragment shader: " << fragmentPath << std::endl;
		return nullptr;
	}
	
	return newShader;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::loadSprite(const std::string& spriteName, 
															  const std::string& textureName, 
															  const std::string& shaderName, 
															  const unsigned int width, 
															  const unsigned int height,
															  const std::string& subTextureName)
{
	auto texture = getTexture(textureName);
	if (texture == nullptr)
	{
		std::cerr << "ERROR::Texture " << textureName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto shaderProgram = getShaderProgram(shaderName);
	if (texture == nullptr)
	{
		std::cerr << "ERROR::Shader program " << shaderName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto& newSprite = sprites.emplace(spriteName, std::make_shared<Renderer::Sprite>(texture,
																					 subTextureName,
																					 shaderProgram,
																					 glm::vec2(0.0f, 0.0f),
																					 glm::vec2(width, height))).first->second;
	return newSprite;
}

std::shared_ptr<Renderer::Texture2d> ResourceManager::loadTexture(const std::string& name, const std::string& relativePath)
{
	int nChannels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(resPath + "/" + relativePath).c_str(), &width, &height, &nChannels, 0);

	if (pixels == nullptr)
	{
		std::cerr << "ERROR::Image wasn't loaded: " << resPath + "/" + relativePath << std::endl;
		return nullptr;
	}

	auto& newTexture = textures.emplace(name, std::make_shared<Renderer::Texture2d>(width, 
																					height, 
																					pixels, 
																					nChannels,
																					GL_NEAREST, 
																					GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<Renderer::Texture2d> ResourceManager::loadTextureAtlas(const std::string& textureName, 
																	   const std::string& texturePath,
																	   const std::vector<std::string>& subTextures,
																	   const unsigned int subTextureWidth, 
																	   const unsigned int subTextureHeight)
{
	auto texture = loadTexture(textureName, texturePath);

	if (texture != nullptr)
	{
		const unsigned int textureWidth = texture->getWidth();
		const unsigned int textureHeight = texture->getHeight();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHeight;

		for (const auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, 
								   static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth,
								 static_cast<float>(currentTextureOffsetY) / textureHeight);

			texture->addSubTexture(currentSubTextureName, leftBottomUV, rightTopUV);

			currentTextureOffsetX += subTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHeight;
			}
		}
	}

	return texture;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::getAnimatedSprite(const std::string& name)
{
	AnimatedSpriteMap::const_iterator it = animatedSprites.find(name);

	if (it == animatedSprites.end())
	{
		std::cerr << "ERROR::Sprite " << name << " wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& name)
{
	ShaderProgramMap::const_iterator it = shaderPrograms.find(name);

	if (it == shaderPrograms.end())
	{
		std::cerr << "ERROR::Shader " << name << "  wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::getSprite(const std::string& name)
{
	SpriteMap::const_iterator it = sprites.find(name);

	if (it == sprites.end())
	{
		std::cerr << "ERROR::Sprite " << name << " wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Renderer::Texture2d> ResourceManager::getTexture(const std::string& name)
{
	TextureMap::const_iterator it = textures.find(name);

	if (it == textures.end())
	{
		std::cerr << "ERROR::Texture " << name << "  wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

void ResourceManager::setExecutablePath(const std::string& path)
{
	size_t found = path.find_last_of("/\\");
	resPath = path.substr(0, found);
}

void ResourceManager::unloadAllResources()
{
	animatedSprites.clear();
	shaderPrograms.clear();
	sprites.clear();
	textures.clear();
}

std::string ResourceManager::getFileText(const std::string& relativePath)
{
	std::fstream f;

	f.open(resPath + "/" + relativePath, std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "ERROR::File wasn't opened: " << resPath + "/" + relativePath << std::endl;
		return std::string();
	}

	std::stringstream buffer;
	buffer << f.rdbuf();

	return buffer.str();
}
