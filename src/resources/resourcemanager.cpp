#include "resourcemanager.h"

#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::AnimatedSpriteMap ResourceManager::animatedSprites;
ResourceManager::ShaderProgramMap ResourceManager::shaderPrograms;
ResourceManager::SpriteMap ResourceManager::sprites;
ResourceManager::TextureMap ResourceManager::textures;
ResourceManager::TextureAtlasMap ResourceManager::textureAtlases;
ResourceManager::LevelMap ResourceManager::levels;
std::string ResourceManager::resPath;

ResourceManager::AnimatedSpritePtr ResourceManager::getAnimatedSprite(const std::string& name)
{
	AnimatedSpriteMap::const_iterator it = animatedSprites.find(name);

	if (it == animatedSprites.end())
	{
		std::cerr << "ERROR::Sprite " << name << " wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

ResourceManager::LevelMap ResourceManager::getLevels()
{
	return levels;
}

ResourceManager::ShaderProgramPtr ResourceManager::getShaderProgram(const std::string& name)
{
	ShaderProgramMap::const_iterator it = shaderPrograms.find(name);

	if (it == shaderPrograms.end())
	{
		std::cerr << "ERROR::Shader " << name << "  wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

ResourceManager::SpritePtr ResourceManager::getSprite(const std::string& name)
{
	SpriteMap::const_iterator it = sprites.find(name);

	if (it == sprites.end())
	{
		std::cerr << "ERROR::Sprite " << name << " wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

ResourceManager::Texture2dPtr ResourceManager::getTexture(const std::string& name)
{
	TextureMap::const_iterator it = textures.find(name);

	if (it == textures.end())
	{
		std::cerr << "ERROR::Texture " << name << "  wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

ResourceManager::TextureAtlasPtr ResourceManager::getTextureAtlas(const std::string& name)
{
	TextureAtlasMap::const_iterator it = textureAtlases.find(name);

	if (it == textureAtlases.end())
	{
		std::cerr << "ERROR::Texture " << name << "  wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

ResourceManager::AnimatedSpritePtr ResourceManager::loadAnimatedSprite(const std::string& spriteName,
																	   const std::string& textureName, 
																	   const std::string& shaderName,
																	   const std::string& subTextureName)
{
	auto textureAtlas = getTextureAtlas(textureName);
	if (textureAtlas == nullptr)
	{
		std::cerr << "ERROR::Texture " << textureName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto shaderProgram = getShaderProgram(shaderName);
	if (shaderProgram == nullptr)
	{
		std::cerr << "ERROR::Shader program " << shaderName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto& newAnimatedSprite = animatedSprites.emplace(spriteName, std::make_shared<RenderEngine::AnimatedSprite>(textureAtlas,
																												 shaderProgram,
																												 subTextureName)).first->second;
	return newAnimatedSprite;
}

bool ResourceManager::loadJsonResources(const std::string& jsonPath)
{
	const std::string jsonString = getFileText(jsonPath);

	if (jsonString.empty())
	{
		std::cerr << "ERROR::No JSON resource file in " << jsonPath << std::endl;
		return false;
	}

	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(jsonString.c_str());

	if (!parseResult)
	{
		std::cerr << "ERROR::JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) << "(" << parseResult.Offset() << "), file " << jsonPath << std::endl;
		return false;
	}

	auto shaderIterator = document.FindMember("shaders");
	if (shaderIterator != document.MemberEnd())
	{
		for (const auto& currentShader : shaderIterator->value.GetArray())
		{
			const std::string name = currentShader["name"].GetString();
			const std::string filePath_v = currentShader["filePath_v"].GetString();
			const std::string filePath_f = currentShader["filePath_f"].GetString();

			loadShaderProgram(name, filePath_v, filePath_f);
		}
	}

	auto texturesIterator = document.FindMember("textures");
	if (texturesIterator != document.MemberEnd())
	{
		for (const auto& currentTexture : texturesIterator->value.GetArray())
		{
			const std::string name = currentTexture["name"].GetString();
			const std::string filePath = currentTexture["filePath"].GetString();

			loadTexture(name, filePath);
		}
	}

	auto textureAtlasesIterator = document.FindMember("textureAtlases");
	if (textureAtlasesIterator != document.MemberEnd())
	{
		for (const auto& currentTextureAtlas : textureAtlasesIterator->value.GetArray())
		{
			const std::string name = currentTextureAtlas["name"].GetString();
			const std::string filePath = currentTextureAtlas["filePath"].GetString();
			const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetInt();
			const unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetInt();

			const auto subTextureArray = currentTextureAtlas["subTextures"].GetArray();	
			std::vector<std::string> subTextures;
			subTextures.reserve(subTextureArray.Size());
			for (const auto& currentSubTexture : subTextureArray)
				subTextures.emplace_back(currentSubTexture.GetString());

			loadTextureAtlas(name, filePath, subTextures, subTextureWidth, subTextureHeight);
		}
	}

	auto spritesIterator = document.FindMember("sprites");
	if (spritesIterator != document.MemberEnd())
	{
		for (const auto& currentSprite : spritesIterator->value.GetArray())
		{
			const std::string name = currentSprite["name"].GetString();
			const std::string textureAtlasName = currentSprite["textureAtlas"].GetString();
			const std::string shaderName = currentSprite["shader"].GetString();
			const std::string subTextureName = currentSprite["subTextureName"].GetString();

			if (subTextureName.empty())
				loadSprite(name, textureAtlasName, shaderName);
			else
				loadSprite(name, textureAtlasName, shaderName, subTextureName);
		}
	}

	auto animatedSpritesIterator = document.FindMember("animatedSprites");
	if (animatedSpritesIterator != document.MemberEnd())
	{
		for (const auto& currentAnimatedSprite : animatedSpritesIterator->value.GetArray())
		{
			const std::string name = currentAnimatedSprite["name"].GetString();
			const std::string textureAtlasName = currentAnimatedSprite["textureAtlas"].GetString();
			const std::string shaderName = currentAnimatedSprite["shader"].GetString();
			const std::string intialSubTextureName = currentAnimatedSprite["initialSubTexture"].GetString();

			auto animatedSprite = loadAnimatedSprite(name, textureAtlasName, shaderName, intialSubTextureName);
			if (animatedSprite == nullptr)
				continue;

			const auto statesArray = currentAnimatedSprite["states"].GetArray();
			for (const auto& currentState : statesArray)
			{
				const std::string stateName = currentState["stateName"].GetString();

				const auto framesArray = currentState["frames"].GetArray();
				std::vector<std::pair<std::string, uint64_t>> frames;
				frames.reserve(framesArray.Size());
				for (const auto& currentFrame : framesArray)
				{
					const std::string subTexture = currentFrame["subTexture"].GetString();
					const uint64_t duration = currentFrame["duration"].GetInt();

					frames.emplace_back(std::pair<std::string, uint64_t>(subTexture, duration));
				}

				animatedSprite->insertState(stateName, frames);
			}
		}
	}
	
	auto levelsIterator = document.FindMember("levels");
	if (levelsIterator != document.MemberEnd())
	{
		for (const auto& currentLevel : levelsIterator->value.GetArray())
		{
			const auto description = currentLevel["description"].GetArray();
			std::vector<std::string> levelRows;
			levelRows.reserve(description.Size());
			size_t maxLength = 0;
			for (const auto& row : description)
			{
				levelRows.emplace_back(row.GetString());

				if (maxLength < levelRows.back().length())
					maxLength = levelRows.back().length();
			}

			for (auto& row : levelRows)
			{
				while (row.length() < maxLength)
					row.append("D");
			}

			levels.push_back(std::move(levelRows));
		}
	}

	return true;
}

ResourceManager::ShaderProgramPtr ResourceManager::loadShaderProgram(const std::string& name, 
																	 const std::string& vertexPath,	
																	 const std::string& fragmentPath)
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

	auto& newShader = shaderPrograms.emplace(name, std::make_shared<RenderEngine::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (!newShader->isCompiled())
	{
		std::cerr << "ERROR::Shader program wasn't loaded: \n" 
				  << "Vertex shader: " << vertexPath << "\n" 
				  << "Fragment shader: " << fragmentPath << std::endl;
		return nullptr;
	}
	
	return newShader;
}

ResourceManager::SpritePtr ResourceManager::loadSprite(const std::string& spriteName,
													   const std::string& textureName, 
													   const std::string& shaderName,
													   const std::string& subTextureName)
{
	auto textureAtlas = getTextureAtlas(textureName);
	if (textureAtlas == nullptr)
	{
		std::cerr << "ERROR::Texture " << textureName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto shaderProgram = getShaderProgram(shaderName);
	if (shaderProgram == nullptr)
	{
		std::cerr << "ERROR::Shader program " << shaderName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto& newSprite = sprites.emplace(spriteName, std::make_shared<RenderEngine::Sprite>(textureAtlas,
																						 shaderProgram,
																						 subTextureName)).first->second;
	return newSprite;
}

ResourceManager::SpritePtr ResourceManager::loadSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderName)
{
	auto textureAtlas = getTexture(textureName);
	if (textureAtlas == nullptr)
	{
		std::cerr << "ERROR::Texture " << textureName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto shaderProgram = getShaderProgram(shaderName);
	if (shaderProgram == nullptr)
	{
		std::cerr << "ERROR::Shader program " << shaderName << " for sprite " << spriteName << " wasn't found!" << std::endl;
		return nullptr;
	}

	auto& newSprite = sprites.emplace(spriteName, std::make_shared<RenderEngine::Sprite>(textureAtlas,
																						 shaderProgram)).first->second;

	return newSprite;
}

ResourceManager::Texture2dPtr ResourceManager::loadTexture(const std::string& name, const std::string& relativePath)
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

	auto& newTexture = textures.emplace(name, std::make_shared<RenderEngine::Texture2d>(pixels,
																						nChannels,
																						width, 
																						height, 
																						GL_NEAREST, 
																						GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return newTexture;
}

ResourceManager::TextureAtlasPtr ResourceManager::loadTextureAtlas(const std::string& textureAtlasName,
																   const std::string& textureAtlasPath,
																   const std::vector<std::string>& subTextures,
																   const unsigned int subTextureWidth, 
																   const unsigned int subTextureHeight)
{
	int nChannels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(resPath + "/" + textureAtlasPath).c_str(), &width, &height, &nChannels, 0);

	if (pixels == nullptr)
	{
		std::cerr << "ERROR::Image wasn't loaded: " << resPath + "/" + textureAtlasPath << std::endl;
		return nullptr;
	}

	auto& newTextureAtlas = textureAtlases.emplace(textureAtlasName, std::make_shared<RenderEngine::TextureAtlas>(pixels,
																												  nChannels,
																												  width,
																												  height,
																												  GL_NEAREST,
																												  GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);

	if (newTextureAtlas != nullptr)
	{
		const unsigned int textureWidth = newTextureAtlas->getWidth();
		const unsigned int textureHeight = newTextureAtlas->getHeight();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHeight;

		for (const auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, 
								   static_cast<float>(currentTextureOffsetY + 0.01f - subTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth - 0.01f) / textureWidth,
								 static_cast<float>(currentTextureOffsetY - 0.01f) / textureHeight);

			newTextureAtlas->addSubTexture(currentSubTextureName, leftBottomUV, rightTopUV);

			currentTextureOffsetX += subTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHeight;
			}
		}
	}

	return newTextureAtlas;
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
