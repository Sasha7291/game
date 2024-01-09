#pragma once

#include <glad/glad.h>

namespace Renderer
{
	class EBO
	{
	public:
		EBO();
		EBO(const EBO&) = delete;
		EBO(EBO&& ebo);
		~EBO();

		void bind() const;
		void init(const void* data, const unsigned int size);
		void unbind() const;

		EBO& operator=(EBO&& ebo) noexcept;
		EBO& operator=(const EBO&) = delete;

	private:
		GLuint id;

	};
}