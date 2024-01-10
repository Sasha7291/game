#pragma once

#include "vbo.h"
#include "vbolayout.h"

namespace RenderEngine
{
	class VAO
	{
	public:
		VAO();
		VAO(const VAO&) = delete;
		VAO(VAO&& vao) noexcept;
		~VAO();

		void addBuffer(const VBO& vbo, const VboLayout& layout);
		void bind() const;
		void unbind() const;

		VAO& operator=(VAO&& vao) noexcept;
		VAO& operator=(const VAO&) = delete;

	private:
		GLuint id;
		unsigned int elementsCount;

	};
}