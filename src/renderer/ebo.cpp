#include "ebo.h"

namespace Renderer
{
	EBO::EBO()
		: id(0) {}

	EBO::EBO(EBO&& ebo)
	{
		id = ebo.id;
		ebo.id = 0;
	}

	EBO::~EBO()
	{
		glDeleteBuffers(1, &id);
	}

	void EBO::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void EBO::init(const void* data, const unsigned int size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void EBO::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	EBO& EBO::operator=(EBO&& ebo) noexcept
	{
		id = ebo.id;
		ebo.id = 0;

		return *this;
	}
}