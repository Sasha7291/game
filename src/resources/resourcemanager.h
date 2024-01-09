#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../renderer/shaderprogram.h"
#include "../renderer/sprite.h"
#include "../renderer/texture2d.h"

/**
@brief ����� ��������� ��������
@details ������ ����� ������������ �������� �������� ��������� ��������,
			�������, ���������� �������, �������� � �.�., �����������
			��� ���������� � ��������� �������.
*/
class ResourceManager
{
public:
	/**
	@brief �������� ����������� ��������� ��������
	@details ������ �������� ��������, ��������� ���� �
			 ��������.
	@param[in] path ���� � ��������
	*/
	explicit ResourceManager(const std::string& path);
	~ResourceManager() = default;

	/**
	@brief �������� ��������� ���������
	@details ��������� ��������� ��������� � ���������� �
			 ���.
	@param[in] name ��� �������
	@param[in] vertexPath ���� � ����� ����������� �������
	@param[in] fragmentPath ���� � ����� ������������ �������
	@return ��������� �� ��������� ��������� ���������
	*/
	std::shared_ptr<Renderer::ShaderProgram> loadShaderProgram(const std::string& name, 
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
	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName, 
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
	std::shared_ptr<Renderer::Texture2d> loadTexture(const std::string& name, const std::string& relativePath);
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
	std::shared_ptr<Renderer::Texture2d> loadTextureAtlas(const std::string& textureName,
														  const std::string& texturePath,
														  const std::vector<std::string>& subTextures,
														  const unsigned int subTextureWidth,
														  const unsigned int subTextureHeight);
	/**
	@brief ���������� ��������� ��������� �� �����
	@param[in] name ��� �������
	@return ��������� �� ��������� ���������
	*/
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& name) const;
	/**
	@brief ���������� ������ �� �����
	@param[in] name ��� �������
	@return ��������� �� ������
	*/
	std::shared_ptr<Renderer::Sprite> getSprite(const std::string& name) const;
	/**
	@brief ���������� �������� �� �����
	@param[in] name ��� ��������
	@return ��������� �� ��������
	*/
	std::shared_ptr<Renderer::Texture2d> getTexture(const std::string& name) const;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	/**
	@brief ������ ����
	@param[in] relativePath ������������� ���� �� �����
	@return ����������� ������
	*/
	std::string getFileText(const std::string& relativePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpriteMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2d>> TextureMap;
	
	ShaderProgramMap shaderPrograms; //!< ������ ��� ��������� ��������
	SpriteMap sprites; //!< ������ ��� ��������
	TextureMap textures; //!< ������ ��� �������

	std::string path; //!< ���� � ��������
};