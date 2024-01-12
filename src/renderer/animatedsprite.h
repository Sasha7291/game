#pragma once

#include "sprite.h"

#include <vector>

/**
namespace RenderEngine
@brief Пространство имён RenderEngine
@details Данное пространство имён содержит все классы,
		  необходимые для рендеринга и отрисовки графики.
*/
namespace RenderEngine
{
	/**
	@brief Класс анимированного спрайта
	@details Данный класс осуществляет создание анимированного спрайта.
	*/
	class AnimatedSprite : public Sprite
	{
	public:
		/**
		@brief Основной конструктор анимированного спрайта
		@details Данный конструктор создаёт анимированный спрайт на основе шейдерной 
				 программы и субтекстуры из текстурного атласа.
		@param[in] texture Текстура (как правило текстурный атлас)
		@param[in] initialSubTexture Название субтекстуры из текстурного атласа
		@param[in] shaderProgram Шейдерная программа
		@param[in] position Позиция спрайта
		@param[in] size Размер спрайта
		@param[in] rotationAngle Угол поворота спрайта
		*/
		explicit AnimatedSprite(const std::shared_ptr<Texture2d> texture,
								const std::string& initialSubTexture,
								const std::shared_ptr<ShaderProgram> shaderProgram);

		/**
		@brief Добавление нового состояния анимации
		@details Добавляет новое состояние анимации, устанавливая ему имя и
				 субтекстуру и продолжительность её показа.
		@param[in] name Устанавливаемое имя состояния
		@param[in] subTectureDuration Название соответсвующей субтекстуры и продолжительность состояния
		*/
		void insertState(const std::string& name, const std::vector<std::pair<std::string, uint64_t>>& subTectureDuration);
		/**
		@brief Рендеринг анимированного спрайта
		@details Рендерит анимированный спрайт по аналогии с базовым
				 спрайтом. При смене состояния заменяет субтекстуру.
		*/
		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
		/**
		@brief Установка определённого состояния
		@param[in] name Имя устаналиваемого состояния
		*/
		void setState(const std::string& name);
		/**
		@brief Обновление состояние спрайта
		@param[in] delta Частота обновления
		*/
		void update(const uint64_t delta);

	private:
		/// Список состояний анимации
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> statesMap; 
		/// Текущее состояние анимации
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator currentAnimationDurations; 
		/// Индекс текущего кадра
		size_t currentFrame = 0; 
		/// Текущий момент времени анимации
		uint64_t currentAnimationTime = 0; 
		/// Загруженность кадров (показывает, нужно ли подгрузить новую текстуру)
		mutable bool dirty = false; 

	};
}