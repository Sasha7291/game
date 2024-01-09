#pragma once

#include "../resources/resourcemanager.h"
#include "tank.h"
#include <GLFW/glfw3.h>

#include <array>

/**
@brief Основной класс игры
@details В данном классе происходит инициализация ресурсов
		 игры, обработка событий, основная логика и т.д.
*/
class Game
{
public:
	/**
	@brief Основной конструктор класса игры
	@details Устанавливает размер окна
	@param[in] ws Устанавливаемый размер окна
	*/
	explicit Game(const glm::ivec2& ws);
	/**
	@brief Деструктор класса игры
	*/
	~Game();

	/**
	@brief Инициализация класса игры
	@details Подгружает необходимые ресурсы, загружает
			 шейдеры и текстуры, устанавливает основные
			 события.
	*/
	bool init();
	/**
	@brief Рендеринг игры
	*/
	void render();
	/**
	@brief Запись состояния нажатия клавиши
	@param[in] key Код клавиши
	@param[in] action Состояние нажатия клавиши
	*/
	void setKey(const int key, const int action);
	/**
	@brief Обновление событий игры
	@param[in] delta Частота обновления
	*/
	void update(const uint64_t delta);

private:
	/// Список кодов клавиш
	std::array<bool, 349> keys;

	/// Состояния игры:
	/// Active - игра работае;
	/// Pause - пауза
	enum GameState
	{
		Active,
		Pause
	};

	/// Текущее состояние игры
	GameState currentGameState;
	/// Размер выводимого окна
	glm::ivec2 windowSize;

	std::unique_ptr<Tank> tank;
};