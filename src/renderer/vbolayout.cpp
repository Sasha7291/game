#include "vbolayout.h"

namespace Renderer
{
	VboLayout::VboLayout()
		: stride(0)
	{}

	void VboLayout::addElementFloat(const unsigned int count, const bool normalized)
	{
		layoutElements.push_back({ static_cast<GLint>(count), GL_FLOAT, normalized, count * static_cast<unsigned int>(sizeof(GLfloat)) });
		stride += layoutElements.back().size;
	}

	const std::vector<VboLayoutElement>& VboLayout::getLayoutElements() const
	{
		return layoutElements;
	}

	unsigned int VboLayout::getStride() const
	{
		return stride;
	}

	void VboLayout::reserveElements(const size_t count)
	{
		layoutElements.reserve(count);
	}
}