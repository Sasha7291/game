#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
	class VBO
	{
	public:
		VBO();
		VBO(const VBO&) = delete;
		VBO(VBO&& vbo) noexcept;
		~VBO();
		
		void bind() const;
		void init(const void* data, const unsigned int size);
		void unbind() const;
		void update(const void* data, const unsigned int size) const;
		
		VBO& operator=(const VBO&) = delete;
		VBO& operator=(VBO&& vbo) noexcept;

	private:
		GLuint id;

	};
}