#pragma once

#include "sprite.h"

#include <vector>

/**
namespace RenderEngine
@brief ������������ ��� RenderEngine
@details ������ ������������ ��� �������� ��� ������,
		  ����������� ��� ���������� � ��������� �������.
*/
namespace RenderEngine
{
	/**
	@brief ����� �������������� �������
	@details ������ ����� ������������ �������� �������������� �������.
	*/
	class AnimatedSprite : public Sprite
	{
	public:
		/**
		@brief �������� ����������� �������������� �������
		@details ������ ����������� ������ ������������� ������ �� ������ ��������� 
				 ��������� � ����������� �� ����������� ������.
		@param[in] texture �������� (��� ������� ���������� �����)
		@param[in] initialSubTexture �������� ����������� �� ����������� ������
		@param[in] shaderProgram ��������� ���������
		@param[in] position ������� �������
		@param[in] size ������ �������
		@param[in] rotationAngle ���� �������� �������
		*/
		explicit AnimatedSprite(const std::shared_ptr<Texture2d> texture,
								const std::string& initialSubTexture,
								const std::shared_ptr<ShaderProgram> shaderProgram);

		/**
		@brief ���������� ������ ��������� ��������
		@details ��������� ����� ��������� ��������, ������������ ��� ��� �
				 ����������� � ����������������� � ������.
		@param[in] name ��������������� ��� ���������
		@param[in] subTectureDuration �������� �������������� ����������� � ����������������� ���������
		*/
		void insertState(const std::string& name, const std::vector<std::pair<std::string, uint64_t>>& subTectureDuration);
		/**
		@brief ��������� �������������� �������
		@details �������� ������������� ������ �� �������� � �������
				 ��������. ��� ����� ��������� �������� �����������.
		*/
		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
		/**
		@brief ��������� ������������ ���������
		@param[in] name ��� ��������������� ���������
		*/
		void setState(const std::string& name);
		/**
		@brief ���������� ��������� �������
		@param[in] delta ������� ����������
		*/
		void update(const uint64_t delta);

	private:
		/// ������ ��������� ��������
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> statesMap; 
		/// ������� ��������� ��������
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator currentAnimationDurations; 
		/// ������ �������� �����
		size_t currentFrame = 0; 
		/// ������� ������ ������� ��������
		uint64_t currentAnimationTime = 0; 
		/// ������������� ������ (����������, ����� �� ���������� ����� ��������)
		mutable bool dirty = false; 

	};
}