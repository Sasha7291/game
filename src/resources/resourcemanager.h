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
@brief Класс менеджера ресурсов
@details Данный класс осуществляет загрузку ресурсов шейдерных программ,
			текстур, текстурных атласов, спрайтов и т.д., необходимых
			для рендеринга и отрисовки графики.
*/
class ResourceManager
{
public:
	/**
	@brief Основной конструктор менеджера ресурсов
	@details Создаёт менеджер ресурсов, сохраняет путь к
			 ресурсам.
	@param[in] path Путь к ресурсам
	*/
	explicit ResourceManager(const std::string& path);
	~ResourceManager() = default;

	/**
	@brief Загрузка шейдерной программы
	@details Загружает шейдерную программу и запоминает её
			 имя.
	@param[in] name Имя шейдера
	@param[in] vertexPath Путь к файлу вертексного шейдера
	@param[in] fragmentPath Путь к файлу фрагментного шейдера
	@return Указатель на созданную шейдерную программу
	*/
	std::shared_ptr<Renderer::ShaderProgram> loadShaderProgram(const std::string& name, 
															   const std::string& vertexPath, 
															   const std::string& fragmentPath);
	/**
	@brief Загрузка спрайта
	@details Загружает спрайт и запоминает его имя.
	@param[in] spriteName Имя спрайта
	@param[in] textureName Имя текстуры для установки в спрайт
	@param[in] shaderName Имя шейдерной программы для установки в спрайт
	@param[in] width Ширина спрайта
	@param[in] height Высота спрайта
	@param[in] subTextureName Имя субтекстуры, устанавливаемой в спрайт
	@return Указатель на созданный спрайт
	*/
	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName, 
												 const std::string& textureName, 
												 const std::string& shaderName,
												 const unsigned int width,
												 const unsigned int height,
												 const std::string& subTextureName = "DefaultSubTexture");
	/**
	@brief Загрузка текстуры
	@details Загружает текстуру и запоминает её имя.
	@param[in] name Имя шейдера
	@param[in] relativePath Относительный путь к текстуре 
	@return Указатель на созданную структуру
	*/
	std::shared_ptr<Renderer::Texture2d> loadTexture(const std::string& name, const std::string& relativePath);
	/**
	@brief Загрузка текстурного атласа
	@details Загружает текстурный атлас и запоминает его имя
			 (в список текстур).
	@param[in] textureName Имя текстуры
	@param[in] texturePath Относительный путь к текстуре 
	@param[in] subTextures Список имён субтекстур
	@param[in] subTextureWidth Ширина субтекстур
	@param[in] subTextureHeight Высота субтекстур
	@return Указатель на созданный текстурный атлас
	*/
	std::shared_ptr<Renderer::Texture2d> loadTextureAtlas(const std::string& textureName,
														  const std::string& texturePath,
														  const std::vector<std::string>& subTextures,
														  const unsigned int subTextureWidth,
														  const unsigned int subTextureHeight);
	/**
	@brief Возвращает шейдерную программу по имени
	@param[in] name Имя шейдера
	@return Указатель на шейдерную программу
	*/
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& name) const;
	/**
	@brief Возвращает спрайт по имени
	@param[in] name Имя спрайта
	@return Указатель на спрайт
	*/
	std::shared_ptr<Renderer::Sprite> getSprite(const std::string& name) const;
	/**
	@brief Возвращает текстуру по имени
	@param[in] name Имя текстуры
	@return Указатель на текстуру
	*/
	std::shared_ptr<Renderer::Texture2d> getTexture(const std::string& name) const;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	/**
	@brief Читает файл
	@param[in] relativePath Относительный путь до файла
	@return Прочитанную строку
	*/
	std::string getFileText(const std::string& relativePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpriteMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2d>> TextureMap;
	
	ShaderProgramMap shaderPrograms; //!< Список имён шейдерных программ
	SpriteMap sprites; //!< Список имён спрайтов
	TextureMap textures; //!< Список имён текстур

	std::string path; //!< Путь к ресурсам
};