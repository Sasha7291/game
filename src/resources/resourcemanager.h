#pragma once

#include "../renderer/animatedsprite.h"

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"

#include <fstream>
#include <iostream>
#include <sstream>

class ResourceManager
{
private:
	typedef std::shared_ptr<RenderEngine::AnimatedSprite> AnimatedSpritePtr;
	typedef std::shared_ptr<RenderEngine::ShaderProgram> ShaderProgramPtr;
	typedef std::shared_ptr<RenderEngine::Sprite> SpritePtr;
	typedef std::shared_ptr<RenderEngine::Texture2d> Texture2dPtr;
	typedef std::shared_ptr<RenderEngine::TextureAtlas> TextureAtlasPtr;

	typedef std::map<const std::string, AnimatedSpritePtr> AnimatedSpriteMap;
	typedef std::vector<std::vector<std::string>> LevelMap;
	typedef std::map<const std::string, ShaderProgramPtr> ShaderProgramMap;
	typedef std::map<const std::string, SpritePtr> SpriteMap;
	typedef std::map<const std::string, Texture2dPtr> TextureMap;
	typedef std::map<const std::string, TextureAtlasPtr> TextureAtlasMap;

public:
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager() = delete;

	static AnimatedSpritePtr getAnimatedSprite(const std::string& name);
	static LevelMap getLevels();
	static ShaderProgramPtr getShaderProgram(const std::string& name);
	static SpritePtr getSprite(const std::string& name);
	static Texture2dPtr getTexture(const std::string& name);
	static TextureAtlasPtr getTextureAtlas(const std::string& name);

	static AnimatedSpritePtr loadAnimatedSprite(const std::string& spriteName,
												const std::string& textureName,
												const std::string& shaderName,
												const std::string& subTextureName);
	static bool loadJsonResources(const std::string& jsonPath);
	static ShaderProgramPtr loadShaderProgram(const std::string& name,
											  const std::string& vertexPath, 
											  const std::string& fragmentPath);
	static SpritePtr loadSprite(const std::string& spriteName,
								const std::string& textureName, 
								const std::string& shaderName,
								const std::string& subTextureName);
	static SpritePtr loadSprite(const std::string& spriteName,
								const std::string& textureName,
								const std::string& shaderName);
	static Texture2dPtr loadTexture(const std::string& name, 
									const std::string& relativePath);
	static TextureAtlasPtr loadTextureAtlas(const std::string& textureAtlasName,
											const std::string& textureAtlasPath,
											const std::vector<std::string>& subTextures,
											const unsigned int subTextureWidth,
											const unsigned int subTextureHeight);

	static void setExecutablePath(const std::string& path);
	static void unloadAllResources();

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	static std::string getFileText(const std::string& relativePath);
	
	static AnimatedSpriteMap animatedSprites; 
	static ShaderProgramMap shaderPrograms;
	static SpriteMap sprites;
	static TextureMap textures;
	static TextureAtlasMap textureAtlases;
	static LevelMap levels;

	static std::string resPath;

};