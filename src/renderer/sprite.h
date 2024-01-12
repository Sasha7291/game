#pragma once

#include "renderer.h"
#include "shaderprogram.h"
#include "texture2d.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <memory>

/**
namespace RenderEngine
@brief ������������ ��� RenderEngine
@details ������ ������������ ��� �������� ��� ������,
		  ����������� ��� ���������� � ��������� �������.
*/
namespace RenderEngine 
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
					    const std::shared_ptr<ShaderProgram> shaderProgram);
		/**
		@brief ���������� �������
		*/
		~Sprite();

		/**
		@brief ��������� �������
		@details �������� ������, ������������ ��� � ����������� �������,
				 ����������� �� �������� ���� � ����������� ������.
		*/
		virtual void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const;
		
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	protected:
		/// �������� �������
		std::shared_ptr<Texture2d> texture; 
		/// ��������� ��������� �������
		std::shared_ptr<ShaderProgram> shaderProgram;
		/// VAO
		VAO vao; 
		/// ���������� VBO
		VBO vertexVbo; 
		/// ���������� VBO
		VBO textureVbo;
		/// EBO
		EBO ebo;

	};
}