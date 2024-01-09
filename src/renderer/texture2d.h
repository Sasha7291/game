#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <map>
#include <string>

/**
namespace Renderer
@brief Пространство имён Renderer
@details Данное пространство имён содержит все классы,
		 необходимые для рендеринга и отрисовки графики.
*/
namespace Renderer
{
	/**
	@brief Класс двумерной текстуры
	@details Данный класс осуществляет загрузку двумерной тестуры и 
			 добавление субтекстур в случае, если текстура представляет 
			 собой текстурный атлас.
	*/
	class Texture2d
	{
	public:
		/**
		@brief Структура субтекстуры
		@details Данная структура хранит информацию о расположении субтекстуры
				 в текстурном атласе.
		*/
		struct SubTexture2d
		{
			glm::vec2 leftBottomUV; //!< Координаты левого нижнего угла субтекстуры
			glm::vec2 rightTopUV; //!< Координаты верхнего правого угла субтекстуры

			/**
			@brief Основной конструктор субтекстуры
			@details Задаёт позиции левого нижнего и правого верхнего углов
					 субтекстуры на текстурном атласе.
			@param[in] lbUV Устанавливаемая позиция левого нижнего угла
			@param[in] rtUV Устанавливаемая позиция правого верхнего угла
			*/
			explicit SubTexture2d(const glm::vec2& lbUV, const glm::vec2& rtUV) : leftBottomUV(lbUV), rightTopUV(rtUV) {}
			/**
			@brief Конструктор по умолчанию субтекстуры
			@details Задаёт позиции левого нижнего и правого верхнего углов
					 субтекстуры на первую субтекстуру на текстурном атласе.
			*/
			SubTexture2d() : leftBottomUV(0.0f), rightTopUV(1.0f) {}
		};

		/**
		@brief Основной конструктор двумерной текстуры
		@details Создаёт двумерную текстуру заданного размера из массива
				 байтов, полученных из файла с изображением.
		@param[in] width Устанавливаемая ширина текстуры
		@param[in] height Устанавливаемая высота текстуры
		@param[in] data Указатель на массив байтов
		@param[in] channels Количество цветовых каналов
		@param[in] filter Фильтрация изображения текстуры
		@param[in] wrapMode Режим растягивания текстуры на вертексный объект
		*/
		explicit Texture2d(const GLuint width, 
						   const GLuint height, 
						   const unsigned char* data, 
						   const unsigned int channels = 4, 
						   const GLenum filter = GL_LINEAR, 
						   const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		/**
		@brief Конструктор перемещения двумерной текстуры
		@details Выполняет перемещение текстуры в новый объект,
				 информация о текстуре в старом объекте при этом
				 затирается.
		*/
		Texture2d(Texture2d&& texture2d) noexcept;
		/**
		@brief Деструктор двумерной текстуры
		*/
		~Texture2d();

		/**
		@brief Добавление субтекстуры из текстурного аталаса в общий список
		@param[in] name Название субтекстуры
		@param[in] leftBottomUV Позиция левого нижнего угла субтекстуры на текстурном атласе
		@param[in] rightTopUV Позиция правого верхнего угла субтекстуры на текстурном атласе
		*/
		void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		/**
		@brief Привязка текущей текстуры
		@details Делает текущую текстуру основной в контексте OpenGL.
		*/
		void bind() const;
		/**
		@brief Геттер высоты текстуры
		@return Высота текстуры
		*/
		const unsigned int getHeight() const;
		/**
		@brief Геттер субтекстуры
		@return Ссылка на субтекстуру
		*/
		const SubTexture2d& getSubTexture(const std::string& name) const;
		/**
		@brief Геттер ширины текстуры
		@return Ширина текстуры
		*/
		const unsigned int getWidth() const;

		Texture2d& operator=(Texture2d&& texture2d) noexcept;

		Texture2d() = delete;
		Texture2d(const Texture2d&) = delete;
		Texture2d& operator=(const Texture2d&) = delete;

	private:
		/// ID текстуры
		GLuint id; 
		/// Количество цветовых каналов
		GLenum format; 
		/// Ширина текстуры
		unsigned int width; 
		/// Высота текстуры
		unsigned int height; 

		/// Список имён субтекстур
		std::map<std::string, SubTexture2d> subTextures; 

	};
}