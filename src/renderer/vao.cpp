#include "vao.h"

namespace Renderer
{
	VAO::VAO()
		: id(0)
		, elementsCount(0)
	{
		glGenVertexArrays(1, &id);
	}

	VAO::VAO(VAO&& vao) noexcept
	{
		id = vao.id;
		elementsCount = vao.elementsCount;

		vao.id = 0;
		vao.elementsCount = 0;
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &id);
	}

	void VAO::addBuffer(const VBO& vbo, const VboLayout& layout)
	{
		bind();
		vbo.bind();
		const auto& layoutElements = layout.getLayoutElements();
		GLbyte* offset = nullptr;

		for (unsigned int i = 0; i < layoutElements.size(); ++i)
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = elementsCount + i;
			glEnableVertexAttribArray(currentAttribIndex);
			glVertexAttribPointer(currentAttribIndex, 
								  currentLayoutElement.count, 
								  currentLayoutElement.type, 
								  currentLayoutElement.normalized, 
								  layout.getStride(), 
								  offset);
			offset += currentLayoutElement.size;
		}

		elementsCount += static_cast<unsigned int>(layoutElements.size());
	}

	void VAO::bind() const
	{
		glBindVertexArray(id);
	}

	void VAO::unbind() const
	{
		glBindVertexArray(0);
	}

	VAO& VAO::operator=(VAO&& vao) noexcept
	{
		id = vao.id;
		elementsCount = vao.elementsCount;

		vao.id = 0;
		vao.elementsCount = 0;

		return *this;
	}
}