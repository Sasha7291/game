#pragma once

#include "../resources/resourcemanager.h"
#include "tank.h"
#include <GLFW/glfw3.h>

#include <array>

/**
@brief �������� ����� ����
@details � ������ ������ ���������� ������������� ��������
		 ����, ��������� �������, �������� ������ � �.�.
*/
class Game
{
public:
	/**
	@brief �������� ����������� ������ ����
	@details ������������� ������ ����
	@param[in] ws ��������������� ������ ����
	*/
	explicit Game(const glm::ivec2& ws);
	/**
	@brief ���������� ������ ����
	*/
	~Game();

	/**
	@brief ������������� ������ ����
	@details ���������� ����������� �������, ���������
			 ������� � ��������, ������������� ��������
			 �������.
	*/
	bool init();
	/**
	@brief ��������� ����
	*/
	void render();
	/**
	@brief ������ ��������� ������� �������
	@param[in] key ��� �������
	@param[in] action ��������� ������� �������
	*/
	void setKey(const int key, const int action);
	/**
	@brief ���������� ������� ����
	@param[in] delta ������� ����������
	*/
	void update(const uint64_t delta);

private:
	/// ������ ����� ������
	std::array<bool, 349> keys;

	/// ��������� ����:
	/// Active - ���� �������;
	/// Pause - �����
	enum GameState
	{
		Active,
		Pause
	};

	/// ������� ��������� ����
	GameState currentGameState;
	/// ������ ���������� ����
	glm::ivec2 windowSize;

	std::unique_ptr<Tank> tank;
};