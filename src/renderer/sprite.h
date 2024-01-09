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
@brief ������������ ��� Renderer
@details ������ ������������ ��� �������� ��� ������,
		  ����������� ��� ���������� � ��������� �������.
*/
namespace Renderer 
{
	/**
	@brief ����� �������
	@details ������ ����� ������������ �������� �������, ��������� ��������� ��������� �
			 ���������� �����. ������ ������ ����� ����������� �� ����������� �������,
			 ������ ��� ������ � ��������� �� ����������� ����.
	*/
	class Sprite
	{
	public:
		/**
		@brief �������� ����������� �������
		@details ������ ����������� ������ ������ �� ������ ��������� ���������
				 � ����������� �� ����������� ������. 
		@param[in] texture �������� (��� ������� ���������� �����)
		@param[in] initialSubTexture �������� ����������� �� ����������� ������
		@param[in] shaderProgram ��������� ���������
		@param[in] position ������� �������
		@param[in] size ������ �������
		@param[in] rotationAngle ���� �������� �������
		*/
		explicit Sprite(const std::shared_ptr<Texture2d> texture, 
					    const std::string& initialSubTexture,
					    const std::shared_ptr<ShaderProgram> shaderProgram, 
					    const glm::vec2& position = glm::vec2(0.0f), 
					    const glm::vec2& size = glm::vec2(1.0f),
					    const float rotationAngle = 0.0f);
		/**
		@brief ���������� �������
		*/
		~Sprite();

		/**
		@brief ��������� �������
		@details �������� ������, ������������ ��� � ����������� �������,
				 ����������� �� �������� ���� � ����������� ������.
		*/
		void render() const;
		/**
		@brief ��������� ������� �������
		@param[in] position ��������������� �������
		*/
		void setPosition(const glm::vec2& position);
		/**
		@brief ��������� ���� �������� �������
		@param[in] position ��������������� ���� ��������
		*/
		void setRotation(const float rotationAngle);
		/**
		@brief ��������� ������� �������
		@param[in] position ��������������� ������
		*/
		void setSize(const glm::vec2& size);

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	private:
		std::shared_ptr<Texture2d> texture; //!< �������� �������
		std::shared_ptr<ShaderProgram> shaderProgram; //!< ��������� ��������� �������
		glm::vec2 position; //!< ������� �������
		glm::vec2 size; //!< ������ �������
		float rotationAngle; //!< ���� �������� �������
		GLuint vao; //!< VAP
		GLuint vertexVbo; //!< ���������� VBO
		GLuint textureVbo; //!< ���������� VBO

	};
}