#include "ebo.h"

namespace RenderEngine
{
	EBO::EBO()
		: id(0)
		, count(0) {}

	EBO::EBO(EBO&& ebo) noexcept
	{
		id = ebo.id;
		count = ebo.count;

		ebo.id = 0;
		ebo.count = 0;
	}

	EBO::~EBO()
	{
		glDeleteBuffers(1, &id);
	}

	void EBO::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	unsigned int EBO::getCount() const
	{
		return count;
	}

	void EBO::init(const void* data, const unsigned int count)
	{
		this->count = count;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	}

	void EBO::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	EBO& EBO::operator=(EBO&& ebo) noexcept
	{
		id = ebo.id;
		count = ebo.count;

		ebo.id = 0;
		ebo.count = 0;

		return *this;
	}
}