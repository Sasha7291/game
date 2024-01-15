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

namespace RenderEngine 
{
	class ShaderProgram
	{
	public:
		explicit ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		~ShaderProgram();

		bool isCompiled() const;
		void setBool(const std::string& name, const GLboolean value) const;
		void setBoolArray(const std::string& name, const GLsizei size, const GLboolean* data) const;
		void setBvec2(const std::string& name, const GLboolean value1, const GLboolean value2) const;
		void setBvec2Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		void setBvec3(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3) const;
		void setBvec3Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		void setBvec4(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3, const GLboolean value4) const;
		void setBvec4Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		void setFloat(const std::string& name, const GLfloat value) const;
		void setFloatArray(const std::string& name, const GLsizei size, const GLfloat* data) const;
		void setInt(const std::string& name, const GLint value) const;
		void setIntArray(const std::string& name, const GLsizei size, const GLint* data) const;
		void setIvec2(const std::string& name, const GLint value1, const GLint value2) const;
		void setIvec2Array(const std::string& name, const GLsizei size, const GLint* data) const;
		void setIvec3(const std::string& name, const GLint value1, const GLint value2, const GLint value3) const;
		void setIvec3Array(const std::string& name, const GLsizei size, const GLint* data) const;
		void setIvec4(const std::string& name, const GLint value1, const GLint value2, const GLint value3, const GLint value4) const;
		void setIvec4Array(const std::string& name, const GLsizei size, const GLint* data) const;
		void setVec2(const std::string& name, const GLfloat value1, const GLfloat value2) const;
		void setVec2Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		void setVec3(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3) const;
		void setVec3Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		void setVec4(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3, const GLfloat value4) const;
		void setVec4Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		void setUint(const std::string& name, const GLuint value) const;
		void setUintArray(const std::string& name, const GLsizei size, const GLuint* data) const;
		void setUivec2(const std::string& name, const GLuint value1, const GLuint value2) const;
		void setUivec2Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		void setUivec3(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3) const;
		void setUivec3Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		void setUivec4(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3, const GLuint value4) const;
		void setUivec4Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		void setMatrix2(const std::string& name, const glm::mat2& matrix) const;
		void setMatrix2x3(const std::string& name, const glm::mat2x3& matrix) const;
		void setMatrix2x4(const std::string& name, const glm::mat2x4& matrix) const;
		void setMatrix3(const std::string& name, const glm::mat3& matrix) const;
		void setMatrix3x2(const std::string& name, const glm::mat3x2& matrix) const;
		void setMatrix3x4(const std::string& name, const glm::mat3x4& matrix) const;
		void setMatrix4(const std::string& name, const glm::mat4& matrix) const;
		void setMatrix4x2(const std::string& name, const glm::mat4x2& matrix) const;
		void setMatrix4x3(const std::string& name, const glm::mat4x3& matrix) const;

		void use() const;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

	private:
		bool createShader(const std::string& source, const GLenum& type, GLuint& shaderId);

		bool compiled;
		GLuint id; 

	};
}
