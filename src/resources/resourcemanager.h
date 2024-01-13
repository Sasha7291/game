#pragma once

#include "../renderer/animatedsprite.h"

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"

#include <fstream>
#include <iostream>
#include <sstream>

/**
@brief ����� ��������� ��������
@details ������ ����� ������������ �������� �������� ��������� ��������,
		 �������, ���������� �������, �������� � �.�., �����������
		 ��� ���������� � ��������� �������.
*/
class ResourceManager
{
public:
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager() = delete;

	/**
	@brief �������� �������������� �������
	@details ��������� ������������� ������ � ���������� ��� ���.
	@param[in] spriteName ��� �������������� �������
	@param[in] textureName ��� �������� ��� ��������� � ������������� ������
	@param[in] shaderName ��� ��������� ��������� ��� ��������� � ������������� ������
	@param[in] subTextureName ��� �����������, ��������������� � ������������� ������
	@return ��������� �� ��������� ������������� ������
	*/
	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
																			const std::string& textureName,
																			const std::string& shaderName,
																			const std::string& subTextureName = "DefaultSubTexture");

	/**
	@brief �������� ��������� ���������
	@details ��������� ��������� ��������� � ���������� �
			 ���.
	@param[in] jsonPath ���� � ����� �� ������� ��������
	@return true, ���� ���� �� ������� �������� ��� ��������� �������; ����� false
	*/
	static bool loadJsonResources(const std::string& jsonPath);

	/**
	@brief �������� ��������� ���������
	@details ��������� ��������� ��������� � ���������� �
			 ���.
	@param[in] name ��� �������
	@param[in] vertexPath ���� � ����� ����������� �������
	@param[in] fragmentPath ���� � ����� ������������ �������
	@return ��������� �� ��������� ��������� ���������
	*/
	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaderProgram(const std::string& name, 
																		  const std::string& vertexPath, 
																		  const std::string& fragmentPath);

	/**
	@brief �������� �������
	@details ��������� ������ � ���������� ��� ���.
	@param[in] spriteName ��� �������
	@param[in] textureName ��� �������� ��� ��������� � ������
	@param[in] shaderName ��� ��������� ��������� ��� ��������� � ������
	@param[in] subTextureName ��� �����������, ��������������� � ������
	@return ��������� �� ��������� ������
	*/
	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
															const std::string& textureName, 
															const std::string& shaderName,
															const std::string& subTextureName = "DefaultSubTexture");

	/**
	@brief �������� ��������
	@details ��������� �������� � ���������� � ���.
	@param[in] name ��� �������
	@param[in] relativePath ������������� ���� � �������� 
	@return ��������� �� ��������� ���������
	*/
	static std::shared_ptr<RenderEngine::Texture2d> loadTexture(const std::string& name, const std::string& relativePath);

	/**
	@brief �������� ����������� ������
	@details ��������� ���������� ����� � ���������� ��� ���
			 (� ������ �������).
	@param[in] textureName ��� ��������
	@param[in] texturePath ������������� ���� � �������� 
	@param[in] subTextures ������ ��� ����������
	@param[in] subTextureWidth ������ ����������
	@param[in] subTextureHeight ������ ����������
	@return ��������� �� ��������� ���������� �����
	*/
	static std::shared_ptr<RenderEngine::Texture2d> loadTextureAtlas(const std::string& textureName,
																	 const std::string& texturePath,
																	 const std::vector<std::string>& subTextures,
																	 const unsigned int subTextureWidth,
																	 const unsigned int subTextureHeight);

	/**
	@brief ���������� ������������� ������ �� �����
	@param[in] name ��� �������������� �������
	@return ��������� �� ������������� ������
	*/
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& name);

	/**
	@brief ���������� ������ ����������� �������� �������
	@return ������ ����������� �������� �������
	*/
	static std::vector<std::vector<std::string>> getLevels();

	/**
	@brief ���������� ��������� ��������� �� �����
	@param[in] name ��� �������
	@return ��������� �� ��������� ���������
	*/
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& name);

	/**
	@brief ���������� ������ �� �����
	@param[in] name ��� �������
	@return ��������� �� ������
	*/
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& name);

	/**
	@brief ���������� �������� �� �����
	@param[in] name ��� ��������
	@return ��������� �� ��������
	*/
	static std::shared_ptr<RenderEngine::Texture2d> getTexture(const std::string& name);

	/**
	@brief ������������� ���� � ��������
	@param[in] path ���� � ��������
	*/
	static void setExecutablePath(const std::string& path);

	/**
	@brief �������� ���� ��������� ��������
	*/
	static void unloadAllResources();

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	/**
	@brief ������ ����
	@param[in] relativePath ������������� ���� �� �����
	@return ����������� ������
	*/
	static std::string getFileText(const std::string& relativePath);

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpriteMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2d>> TextureMap;
	
	/// ������ ��� ������������� ��������
	static AnimatedSpriteMap animatedSprites; 
	/// ������ ��� ��������� ��������
	static ShaderProgramMap shaderPrograms;
	/// ������ ��� ��������
	static SpriteMap sprites;
	/// ������ ��� �������
	static TextureMap textures;
	/// ������ ����������� �������� �������
	static std::vector<std::vector<std::string>> levels;

	/// ���� � ��������
	static std::string resPath;

};