#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <memory>

#include "texture2d.h"
#include "shaderprogram.h"

/**
namespace Renderer
@brief Пространство имён Renderer
@details Данное пространство имён содержит все классы,
		  необходимые для рендеринга и отрисовки графики.
*/
namespace Renderer 
{
	/**
	@brief Класс спрайта
	@details Данный класс осуществляет создание спрайта, используя шейдерную программу и
			 текстурный атлас. Каждый спрайт можно расположить на определённой позиции,
			 задать его размер и повернуть на определённый угол.
	*/
	class Sprite
	{
	public:
		/**
		@brief Основной конструктор спрайта
		@details Данный конструктор создаёт спрайт на основе шейдерной программы
				 и субтекстуры из текстурного атласа. 
		@param[in] texture Текстура (как правило текстурный атлас)
		@param[in] initialSubTexture Название субтекстуры из текстурного атласа
		@param[in] shaderProgram Шейдерная программа
		@param[in] position Позиция спрайта
		@param[in] size Размер спрайта
		@param[in] rotationAngle Угол поворота спрайта
		*/
		explicit Sprite(const std::shared_ptr<Texture2d> texture, 
					    const std::string& initialSubTexture,
					    const std::shared_ptr<ShaderProgram> shaderProgram, 
					    const glm::vec2& position = glm::vec2(0.0f), 
					    const glm::vec2& size = glm::vec2(1.0f),
					    const float rotationAngle = 0.0f);
		/**
		@brief Деструктор спрайта
		*/
		~Sprite();

		/**
		@brief Рендеринг спрайта
		@details Рендерит спрайт, устанавливая его в определённую позицию,
				 поворачивая на заданный угол и устаналивая размер.
		*/
		void render() const;
		/**
		@brief Установка позиции спрайта
		@param[in] position Устанавливаемая позиция
		*/
		void setPosition(const glm::vec2& position);
		/**
		@brief Установка угла поворота спрайта
		@param[in] position Устанавливаемый угол поворота
		*/
		void setRotation(const float rotationAngle);
		/**
		@brief Установка размера спрайта
		@param[in] position Устанавливаемый размер
		*/
		void setSize(const glm::vec2& size);

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	private:
		std::shared_ptr<Texture2d> texture; //!< Текстура спрайта
		std::shared_ptr<ShaderProgram> shaderProgram; //!< Шейдерная программа спрайта
		glm::vec2 position; //!< Позиция спрайта
		glm::vec2 size; //!< Размер спрайта
		float rotationAngle; //!< Угол поворота спрайта
		GLuint vao; //!< VAP
		GLuint vertexVbo; //!< Вертексный VBO
		GLuint textureVbo; //!< Вертексный VBO

	};
}