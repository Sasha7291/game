#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>

namespace Renderer {
	class ShaderProgram
	{
	public:
		explicit ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		~ShaderProgram();

		bool isCompiled() const;
		void setBool(const std::string& name, const GLboolean value);
		void setFloat(const std::string& name, const GLfloat value);
		void setInt(const std::string& name, const GLint value);
		void use() const;

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

	private:
		bool createShader(const std::string& source, const GLenum& type, GLuint& shaderId);

		bool compiled;
		GLuint id;
	};
}
