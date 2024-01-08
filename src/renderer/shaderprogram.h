/**
 @file shaderprogram.h
 @author STD
 @date 08.01.2024
 @brief ���������� ������ ��������� ���������
 */
#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <string>

/**
namespace Renderer
@brief ������������ ��� Renderer
@details ������ ������������ ��� �������� ��� ������,
		  ����������� ��� ���������� � ��������� �������.
*/
namespace Renderer {
	/**
	@brief ����� ��������� ���������
	@details ������ ����� ������������ �������� ��������� ��������� � � ������������� 
			  �� ����� ���������� �������.
	*/
	class ShaderProgram
	{
	public:
		/**
		@brief �������� ����������� ��������� ���������
		@details ������ ����������� ������ ���������� � ����������� ������ �
				  ������� �� � ��������� ��������� � ����������� ID. � ������ �������
				  ������� ��������� �� ������.
		@param[in] vertexShader  ��� ����������� �������
		@param[in] fragmentShader ��� ������������ �������
		*/
		explicit ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		/**
		@brief ����������� ����������� ��������� ���������
		@details ������ ����������� ��������� ����������� ��������� ���������
				  � ����� ������, ��� ���� ���������� � ��������� ��������� �
				  ���������� ������� ����������.
		*/
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		/**
		@brief ���������� ��������� ���������
		*/
		~ShaderProgram();

		/**
		@brief �������� ���������� ��������� ���������
		@return true, ���� ��������� ��������� ��������������; ����� false
		*/
		bool isCompiled() const;

		/**
		@brief ������ �������� ���� bool � uniform
		@details ������������� �������� ���� bool ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value ��������������� ��������
		*/
		void setBool(const std::string& name, const GLboolean value) const;
		/**
		@brief ������ ������� �������� ���� bool � uniform
		@details ������������� ������ �������� ���� bool ��� ���������� 
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setBoolArray(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief ������ �������� ���� bvec2 � uniform
		@details ������������� �������� ���� bvec2 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2 ��������������� ��������
		*/
		void setBvec2(const std::string& name, const GLboolean value1, const GLboolean value2) const;
		/**
		@brief ������ ������� �������� ���� bvec2 � uniform
		@details ������������� ������ �������� ���� bvec2 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setBvec2Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief ������ �������� ���� bvec3 � uniform
		@details ������������� �������� ���� bvec3 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3 ��������������� ��������
		*/
		void setBvec3(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3) const;
		/**
		@brief ������ ������� �������� ���� bvec3 � uniform
		@details ������������� ������ �������� ���� bvec3 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setBvec3Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief ������ �������� ���� bvec4 � uniform
		@details ������������� �������� ���� bvec4 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3, value4 ��������������� ��������
		*/
		void setBvec4(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3, const GLboolean value4) const;
		/**
		@brief ������ ������� �������� ���� bvec4 � uniform
		@details ������������� ������ �������� ���� bvec4 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setBvec4Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief ������ �������� ���� float � uniform
		@details ������������� �������� ���� float ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value ��������������� ��������
		*/
		void setFloat(const std::string& name, const GLfloat value) const;
		/**
		@brief ������ ������� �������� ���� float � uniform
		@details ������������� ������ �������� ���� float ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setFloatArray(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief ������ ������� �������� ���� int � uniform
		@details ������������� ������ �������� ���� int ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value ��������������� ��������
		*/
		void setInt(const std::string& name, const GLint value) const;
		/**
		@brief ������ ������� �������� ���� int � uniform
		@details ������������� ������ �������� ���� int ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setIntArray(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief ������ ������� �������� ���� ivec2 � uniform
		@details ������������� ������ �������� ���� ivec2 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2 ��������������� ��������
		*/
		void setIvec2(const std::string& name, const GLint value1, const GLint value2) const;
		/**
		@brief ������ ������� �������� ���� ivec2 � uniform
		@details ������������� ������ �������� ���� ivec2 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setIvec2Array(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief ������ ������� �������� ���� ivec3 � uniform
		@details ������������� ������ �������� ���� ivec3 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3 ��������������� ��������
		*/
		void setIvec3(const std::string& name, const GLint value1, const GLint value2, const GLint value3) const;
		/**
		@brief ������ ������� �������� ���� ivec3 � uniform
		@details ������������� ������ �������� ���� ivec3 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setIvec3Array(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief ������ ������� �������� ���� ivec4 � uniform
		@details ������������� ������ �������� ���� ivec4 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3, value4 ��������������� ��������
		*/
		void setIvec4(const std::string& name, const GLint value1, const GLint value2, const GLint value3, const GLint value4) const;
		/**
		@brief ������ ������� �������� ���� ivec4 � uniform
		@details ������������� ������ �������� ���� ivec4 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setIvec4Array(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief ������ �������� ���� vec2 � uniform
		@details ������������� �������� ���� vec2 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2 ��������������� ��������
		*/
		void setVec2(const std::string& name, const GLfloat value1, const GLfloat value2) const;
		/**
		@brief ������ ������� �������� ���� vec2 � uniform
		@details ������������� ������ �������� ���� vec2 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setVec2Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief ������ �������� ���� vec3 � uniform
		@details ������������� �������� ���� vec3 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3 ��������������� ��������
		*/
		void setVec3(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3) const;
		/**
		@brief ������ ������� �������� ���� vec3 � uniform
		@details ������������� ������ �������� ���� vec3 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setVec3Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief ������ �������� ���� vec4 � uniform
		@details ������������� �������� ���� vec4 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3, value4 ��������������� ��������
		*/
		void setVec4(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3, const GLfloat value4) const;
		/**
		@brief ������ ������� �������� ���� vec4 � uniform
		@details ������������� ������ �������� ���� vec4 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setVec4Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief ������ �������� ���� uint � uniform
		@details ������������� �������� ���� uint ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value ��������������� ��������
		*/
		void setUint(const std::string& name, const GLuint value) const;
		/**
		@brief ������ ������� �������� ���� uint � uniform
		@details ������������� ������ �������� ���� uint ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setUintArray(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief ������ �������� ���� uivec2 � uniform
		@details ������������� �������� ���� uivec2 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2 ��������������� ��������
		*/
		void setUivec2(const std::string& name, const GLuint value1, const GLuint value2) const;
		/**
		@brief ������ ������� �������� ���� uivec2 � uniform
		@details ������������� ������ �������� ���� uivec2 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setUivec2Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief ������ �������� ���� uivec3 � uniform
		@details ������������� �������� ���� uivec3 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3 ��������������� ��������
		*/
		void setUivec3(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3) const;
		/**
		@brief ������ ������� �������� ���� uivec3 � uniform
		@details ������������� ������ �������� ���� uivec3 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setUivec3Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief ������ �������� ���� uivec4 � uniform
		@details ������������� �������� ���� uivec4 ��� ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] value1, value2, value3, value4 ��������������� ��������
		*/
		void setUivec4(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3, const GLuint value4) const;
		/**
		@brief ������ ������� �������� ���� uivec4 � uniform
		@details ������������� ������ �������� ���� uivec4 ��� ����������
				 �������� � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] size ������ ������� ������
		@param[in] data ��������� �� ������ ������
		*/
		void setUivec4Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief ������ ������� ������� 2x2 � uniform
		@details ������������� ������� ������� 2x2 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix2(const std::string& name, const glm::mat2& matrix) const;
		/**
		@brief ������ ������� ������� 2x3 � uniform
		@details ������������� ������� ������� 2x3 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix2x3(const std::string& name, const glm::mat2x3& matrix) const;
		/**
		@brief ������ ������� ������� 2x4 � uniform
		@details ������������� ������� ������� 2x4 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix2x4(const std::string& name, const glm::mat2x4& matrix) const;
		/**
		@brief ������ ������� ������� 3x3 � uniform
		@details ������������� ������� ������� 3x3 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix3(const std::string& name, const glm::mat3& matrix) const;
		/**
		@brief ������ ������� ������� 3x2 � uniform
		@details ������������� ������� ������� 3x2 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix3x2(const std::string& name, const glm::mat3x2& matrix) const;
		/**
		@brief ������ ������� ������� 3x4 � uniform
		@details ������������� ������� ������� 3x4 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix3x4(const std::string& name, const glm::mat3x4& matrix) const;
		/**
		@brief ������ ������� ������� 4x4 � uniform
		@details ������������� ������� ������� 4x4 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix4(const std::string& name, const glm::mat4& matrix) const;
		/**
		@brief ������ ������� ������� 4x2 � uniform
		@details ������������� ������� ������� 4x2 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix4x2(const std::string& name, const glm::mat4x2& matrix) const;
		/**
		@brief ������ ������� ������� 4x3 � uniform
		@details ������������� ������� ������� 4x3 � ���������� ��������
				 � ��������� ���������.
		@param[in] name ��� ���������� uniform
		@param[in] matrix ��������������� �������
		*/
		void setMatrix4x3(const std::string& name, const glm::mat4x3& matrix) const;

		/**
		@brief ������������� ��������� ��������� � ���������
		@details ��� ������������� ��������� ��������� � ���������� ���������� ��� 
				 ����� �������� ��������� ����������. ������ ������� ���������� �������
				 ��������� ���������.
		*/
		void use() const;

		/**
		@brief ���������� ��������� ������������
		@details ��� ������������ ������ ������� ������� � �������
				 �� ������ ����������� ����������� �������, �.�. �����
				 ���������� �������� � ����������� ���������� �������,
				 ������� �������� ������������ ���������� �����������
				 ��������� ��������� � ����� ������ ������.
		*/
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

	private:
		/**
		@brief �������� ���������� �������
		@details ������ ������� ������ � ����������� ������ (���������� 
				 ��� �����������) �� ��������� ���� �� ����� GLSL. � ������
				 ��������� ���������� ������� ��������� �� ������.
		@param[in] source ��� �������
		@param[in] type ��� �������
		@param[out] shaderId ID ���������� �������
		*/
		bool createShader(const std::string& source, const GLenum& type, GLuint& shaderId);

		bool compiled; //!< ����, �������� ��������� ���������� ��������� ���������
		GLuint id; //!< ID ��������� ���������

	};
}
