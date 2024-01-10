#pragma once

#include <glad/glad.h>

namespace RenderEngine
{
	class EBO
	{
	public:
		EBO();
		EBO(const EBO&) = delete;
		EBO(EBO&& ebo) noexcept;
		~EBO();

		void bind() const;
		unsigned int getCount() const;
		void init(const void* data, const unsigned int count);
		void unbind() const;

		EBO& operator=(EBO&& ebo) noexcept;
		EBO& operator=(const EBO&) = delete;

	private:
		GLuint id;
		unsigned int count;

	};
}