#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <map>
#include <string>

/**
namespace Renderer
@brief ������������ ��� Renderer
@details ������ ������������ ��� �������� ��� ������,
		 ����������� ��� ���������� � ��������� �������.
*/
namespace Renderer
{
	/**
	@brief ����� ��������� ��������
	@details ������ ����� ������������ �������� ��������� ������� � 
			 ���������� ���������� � ������, ���� �������� ������������ 
			 ����� ���������� �����.
	*/
	class Texture2d
	{
	public:
		/**
		@brief ��������� �����������
		@details ������ ��������� ������ ���������� � ������������ �����������
				 � ���������� ������.
		*/
		struct SubTexture2d
		{
			glm::vec2 leftBottomUV; //!< ���������� ������ ������� ���� �����������
			glm::vec2 rightTopUV; //!< ���������� �������� ������� ���� �����������

			/**
			@brief �������� ����������� �����������
			@details ����� ������� ������ ������� � ������� �������� �����
					 ����������� �� ���������� ������.
			@param[in] lbUV ��������������� ������� ������ ������� ����
			@param[in] rtUV ��������������� ������� ������� �������� ����
			*/
			explicit SubTexture2d(const glm::vec2& lbUV, const glm::vec2& rtUV) : leftBottomUV(lbUV), rightTopUV(rtUV) {}
			/**
			@brief ����������� �� ��������� �����������
			@details ����� ������� ������ ������� � ������� �������� �����
					 ����������� �� ������ ����������� �� ���������� ������.
			*/
			SubTexture2d() : leftBottomUV(0.0f), rightTopUV(1.0f) {}
		};

		/**
		@brief �������� ����������� ��������� ��������
		@details ������ ��������� �������� ��������� ������� �� �������
				 ������, ���������� �� ����� � ������������.
		@param[in] width ��������������� ������ ��������
		@param[in] height ��������������� ������ ��������
		@param[in] data ��������� �� ������ ������
		@param[in] channels ���������� �������� �������
		@param[in] filter ���������� ����������� ��������
		@param[in] wrapMode ����� ������������ �������� �� ���������� ������
		*/
		explicit Texture2d(const GLuint width, 
						   const GLuint height, 
						   const unsigned char* data, 
						   const unsigned int channels = 4, 
						   const GLenum filter = GL_LINEAR, 
						   const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		/**
		@brief ����������� ����������� ��������� ��������
		@details ��������� ����������� �������� � ����� ������,
				 ���������� � �������� � ������ ������� ��� ����
				 ����������.
		*/
		Texture2d(Texture2d&& texture2d) noexcept;
		/**
		@brief ���������� ��������� ��������
		*/
		~Texture2d();

		/**
		@brief ���������� ����������� �� ����������� ������� � ����� ������
		@param[in] name �������� �����������
		@param[in] leftBottomUV ������� ������ ������� ���� ����������� �� ���������� ������
		@param[in] rightTopUV ������� ������� �������� ���� ����������� �� ���������� ������
		*/
		void addSubTexture(const std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		/**
		@brief �������� ������� ��������
		@details ������ ������� �������� �������� � ��������� OpenGL.
		*/
		void bind() const;
		/**
		@brief ������ ������ ��������
		@return ������ ��������
		*/
		const unsigned int getHeight() const;
		/**
		@brief ������ �����������
		@return ������ �� �����������
		*/
		const SubTexture2d& getSubTexture(const std::string& name) const;
		/**
		@brief ������ ������ ��������
		@return ������ ��������
		*/
		const unsigned int getWidth() const;

		Texture2d& operator=(Texture2d&& texture2d) noexcept;

		Texture2d() = delete;
		Texture2d(const Texture2d&) = delete;
		Texture2d& operator=(const Texture2d&) = delete;

	private:
		/// ID ��������
		GLuint id; 
		/// ���������� �������� �������
		GLenum format; 
		/// ������ ��������
		unsigned int width; 
		/// ������ ��������
		unsigned int height; 

		/// ������ ��� ����������
		std::map<std::string, SubTexture2d> subTextures; 

	};
}