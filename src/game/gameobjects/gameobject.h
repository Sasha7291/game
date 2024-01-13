#pragma once

#include "../src/renderer/animatedsprite.h"

/**
@brief Класс-интерфейс для всех игровых объектов
*/
class GameObject
{
public:
	explicit GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual ~GameObject();

	/**
	@brief Рендеринг игрового объекта
	*/
	virtual void render() const = 0;

	/**
	@brief Обновление игрового объекта
	*/
	virtual void update(const uint64_t delta) = 0;

protected:
	/// Позиция игрового объекта
	glm::vec2 position;
	/// Размер игрового объекта
	glm::vec2 size;
	/// Угол поворота игрового объекта
	float rotation;

};