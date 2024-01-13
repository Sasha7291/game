#pragma once

#include "../renderer/animatedsprite.h"

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"

#include <fstream>
#include <iostream>
#include <sstream>

/**
@brief Класс менеджера ресурсов
@details Данный класс осуществляет загрузку ресурсов шейдерных программ,
		 текстур, текстурных атласов, спрайтов и т.д., необходимых
		 для рендеринга и отрисовки графики.
*/
class ResourceManager
{
public:
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager() = delete;

	/**
	@brief Загрузка анимированного спрайта
	@details Загружает анимированный спрайт и запоминает его имя.
	@param[in] spriteName Имя анимированного спрайта
	@param[in] textureName Имя текстуры для установки в анимированный спрайт
	@param[in] shaderName Имя шейдерной программы для установки в анимированный спрайт
	@param[in] subTextureName Имя субтекстуры, устанавливаемой в анимированный спрайт
	@return Указатель на созданный анимированный спрайт
	*/
	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
																			const std::string& textureName,
																			const std::string& shaderName,
																			const std::string& subTextureName = "DefaultSubTexture");

	/**
	@brief Загрузка шейдерной программы
	@details Загружает шейдерную программу и запоминает её
			 имя.
	@param[in] jsonPath Путь к файлу со списком ресурсов
	@return true, если файл со списком ресурсов был распарсен успешно; иначе false
	*/
	static bool loadJsonResources(const std::string& jsonPath);

	/**
	@brief Загрузка шейдерной программы
	@details Загружает шейдерную программу и запоминает её
			 имя.
	@param[in] name Имя шейдера
	@param[in] vertexPath Путь к файлу вертексного шейдера
	@param[in] fragmentPath Путь к файлу фрагментного шейдера
	@return Указатель на созданную шейдерную программу
	*/
	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaderProgram(const std::string& name, 
																		  const std::string& vertexPath, 
																		  const std::string& fragmentPath);

	/**
	@brief Загрузка спрайта
	@details Загружает спрайт и запоминает его имя.
	@param[in] spriteName Имя спрайта
	@param[in] textureName Имя текстуры для установки в спрайт
	@param[in] shaderName Имя шейдерной программы для установки в спрайт
	@param[in] subTextureName Имя субтекстуры, устанавливаемой в спрайт
	@return Указатель на созданный спрайт
	*/
	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
															const std::string& textureName, 
															const std::string& shaderName,
															const std::string& subTextureName = "DefaultSubTexture");

	/**
	@brief Загрузка текстуры
	@details Загружает текстуру и запоминает её имя.
	@param[in] name Имя шейдера
	@param[in] relativePath Относительный путь к текстуре 
	@return Указатель на созданную структуру
	*/
	static std::shared_ptr<RenderEngine::Texture2d> loadTexture(const std::string& name, const std::string& relativePath);

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
	static std::shared_ptr<RenderEngine::Texture2d> loadTextureAtlas(const std::string& textureName,
																	 const std::string& texturePath,
																	 const std::vector<std::string>& subTextures,
																	 const unsigned int subTextureWidth,
																	 const unsigned int subTextureHeight);

	/**
	@brief Возвращает анимированный спрайт по имени
	@param[in] name Имя анимированного спрайта
	@return Указатель на анимированный спрайт
	*/
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& name);

	/**
	@brief Возвращает список символьного описания уровней
	@return Список символьного описания уровней
	*/
	static std::vector<std::vector<std::string>> getLevels();

	/**
	@brief Возвращает шейдерную программу по имени
	@param[in] name Имя шейдера
	@return Указатель на шейдерную программу
	*/
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& name);

	/**
	@brief Возвращает спрайт по имени
	@param[in] name Имя спрайта
	@return Указатель на спрайт
	*/
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& name);

	/**
	@brief Возвращает текстуру по имени
	@param[in] name Имя текстуры
	@return Указатель на текстуру
	*/
	static std::shared_ptr<RenderEngine::Texture2d> getTexture(const std::string& name);

	/**
	@brief Устанавливает путь к ресурсам
	@param[in] path Путь к ресурсам
	*/
	static void setExecutablePath(const std::string& path);

	/**
	@brief Удаление всех созданных ресурсов
	*/
	static void unloadAllResources();

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	/**
	@brief Читает файл
	@param[in] relativePath Относительный путь до файла
	@return Прочитанную строку
	*/
	static std::string getFileText(const std::string& relativePath);

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpriteMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpriteMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2d>> TextureMap;
	
	/// Список имён анимированных спрайтов
	static AnimatedSpriteMap animatedSprites; 
	/// Список имён шейдерных программ
	static ShaderProgramMap shaderPrograms;
	/// Список имён спрайтов
	static SpriteMap sprites;
	/// Список имён текстур
	static TextureMap textures;
	/// Список символьного описания уровней
	static std::vector<std::vector<std::string>> levels;

	/// Путь к ресурсам
	static std::string resPath;

};