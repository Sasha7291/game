#include "renderer.h"

namespace RenderEngine
{
	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::draw(const VAO& vao, const EBO& ebo, const ShaderProgram& shaderProgram)
	{
		shaderProgram.use();
		vao.bind();
		ebo.bind();

		glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	std::string Renderer::getRenderStr()
	{
		return reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER)));
	}

	std::string Renderer::getVersionStr()
	{
		return reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)));
	}

	void Renderer::setClearColor(const GLfloat red, const GLfloat blue, const GLfloat green, const GLfloat alpha)
	{
		glClearColor(red, blue, green, alpha);
	}

	void Renderer::setViewport(const GLuint width, const GLuint height, const GLuint offsetLeft, const GLuint offsetBottom)
	{
		glViewport(offsetLeft, offsetBottom, width, height);
	}
}