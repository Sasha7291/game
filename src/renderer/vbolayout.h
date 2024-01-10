#pragma once

#include <glad/glad.h>

#include <vector>

namespace RenderEngine
{
	struct VboLayoutElement
	{
		GLint count;
		GLenum type;
		GLboolean normalized;
		unsigned int size;
	};

	class VboLayout
	{
	public:
		VboLayout();

		void addElementFloat(const unsigned int count, const bool normalized);
		const std::vector<VboLayoutElement>& getLayoutElements() const;
		unsigned int getStride() const;
		void reserveElements(const size_t count);

	private:
		std::vector<VboLayoutElement> layoutElements;
		unsigned int stride;

	};
}