#pragma once 

#include "shaderprogram.h"
#include "vao.h"
#include "ebo.h"

namespace RenderEngine
{
	class Renderer
	{
	public:
		static void clear();
		static void draw(const VAO& vao, const EBO& ebo, const std::shared_ptr<ShaderProgram> shaderProgram);
		static std::string getRenderStr();
		static std::string getVersionStr();
		static void setClearColor(const GLfloat red, const GLfloat blue, const GLfloat green, const GLfloat alpha);
		static void setViewport(const GLint width, const GLint height, const GLsizei offsetLeft = 0, const GLsizei offsetBottom = 0);
		
	};
}