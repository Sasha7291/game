#include "vbo.h"

namespace RenderEngine
{
	VBO::VBO()
		: id(0) {}

	VBO::VBO(VBO&& vbo) noexcept
	{
		id = vbo.id;

		vbo.id = 0;
	}
	
	VBO::~VBO()
	{
		glDeleteBuffers(1, &id);
	}
	
	void VBO::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	
	void VBO::init(const void* data, const size_t size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	
	void VBO::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	void VBO::update(const void* data, const size_t size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	
	VBO& VBO::operator=(VBO&& vbo) noexcept
	{
		id = vbo.id;

		vbo.id = 0;

		return *this;
	}
}