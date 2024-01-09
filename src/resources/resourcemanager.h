#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../renderer/animatedsprite.h"

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
	@param[in] width ������ �������������� �������
	@param[in] height ������ �������������� �������
	@param[in] subTextureName ��� �����������, ��������������� � ������������� ������
	@return ��������� �� ��������� ������������� ������
	*/
	static std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
																 const std::string& textureName,
																 const std::string& shaderName,
																 const unsigned int width,
																 const unsigned int height,
																 const std::string& subTextureName = "DefaultSubTexture");
	/**
	@brief �������� ��������� ���������
	@details ��������� ��������� ��������� � ���������� �
			 ���.
	@param[in] name ��� �������
	@param[in] vertexPath ���� � ����� ����������� �������
	@param[in] fragmentPath ���� � ����� ������������ �������
	@return ��������� �� ��������� ��������� ���������
	*/
	static std::shared_ptr<Renderer::ShaderProgram> loadShaderProgram(const std::string& name, 
															   const std::string& vertexPath, 
															   const std::string& fragmentPath);
	/**
	@brief �������� �������
	@details ��������� ������ � ���������� ��� ���.
	@param[in] spriteName ��� �������
	@param[in] textureName ��� �������� ��� ��������� � ������
	@param[in] shaderName ��� ��������� ��������� ��� ��������� � ������
	@param[in] width ������ �������
	@param[in] height ������ �������
	@param[in] subTextureName ��� �����������, ��������������� � ������
	@return ��������� �� ��������� ������
	*/
	static std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
												 const std::string& textureName, 
												 const std::string& shaderName,
												 const unsigned int width,
												 const unsigned int height,
												 const std::string& subTextureName = "DefaultSubTexture");
	/**
	@brief �������� ��������
	@details ��������� �������� � ���������� � ���.
	@param[in] name ��� �������
	@param[in] relativePath ������������� ���� � �������� 
	@return ��������� �� ��������� ���������
	*/
	static std::shared_ptr<Renderer::Texture2d> loadTexture(const std::string& name, const std::string& relativePath);
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
	static std::shared_ptr<Renderer::Texture2d> loadTextureAtlas(const std::string& textureName,
														  const std::string& texturePath,
														  const std::vector<std::string>& subTextures,
														  const unsigned int subTextureWidth,
														  const unsigned int subTextureHeight);
	/**
	@brief ���������� ������������� ������ �� �����
	@param[in] name ��� �������������� �������
	@return ��������� �� ������������� ������
	*/
	static std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string& name);
	/**
	@brief ���������� ��������� ��������� �� �����
	@param[in] name ��� �������
	@return ��������� �� ��������� ���������
	*/
	static std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& name);
	/**
	@brief ���������� ������ �� �����
	@param[in] name ��� �������
	@return ��������� �� ������
	*/
	static std::shared_ptr<Renderer::Sprite> getSprite(const std::string& name);
	/**
	@brief ���������� �������� �� �����
	@param[in] name ��� ��������
	@return ��������� �� ��������
	*/
	static std::shared_ptr<Renderer::Texture2d> getTexture(const std::string& name);
	/**
	@brief ������������� ���� � ��������
	@param[in] path ���� � ��������
	*/
	static void setExecutablePath(const std::string& path);
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

	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpriteMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpriteMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2d>> TextureMap;
	
	/// ������ ��� ������������� ��������
	static AnimatedSpriteMap animatedSprites; 
	/// ������ ��� ��������� ��������
	static ShaderProgramMap shaderPrograms;
	/// ������ ��� ��������
	static SpriteMap sprites;
	/// ������ ��� �������
	static TextureMap textures;

	/// ���� � ��������
	static std::string resPath;
};