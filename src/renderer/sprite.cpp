#include "sprite.h"

namespace RenderEngine
{
	Sprite::Sprite(const std::shared_ptr<Texture2d> texture, 
				   const std::shared_ptr<ShaderProgram> shaderProgram)
		: texture(texture)
		, shaderProgram(shaderProgram)
		, vao()
		, textureVbo()
		, vertexVbo()
		, ebo()
	{
		const GLfloat vertexCoord[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};
		createVbo(vertexVbo, vertexCoord, sizeof(vertexCoord));

		const GLfloat textureCoord[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};
		createVbo(textureVbo, textureCoord, sizeof(textureCoord));

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		ebo.init(indices, sizeof(indices));

		vao.unbind();
		ebo.unbind();
	}

	Sprite::Sprite(const std::shared_ptr<TextureAtlas> textureAtlas,
				   const std::shared_ptr<ShaderProgram> shaderProgram,
				   const std::string& initialSubTexture)
		: textureAtlas(textureAtlas)
		, shaderProgram(shaderProgram)
		, vao()
		, textureVbo()
		, vertexVbo()
		, ebo()
	{
		const GLfloat vertexCoord[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};
		createVbo(vertexVbo, vertexCoord, sizeof(vertexCoord));
		
		auto& subTexture = this->textureAtlas->getSubTexture(initialSubTexture);
		const GLfloat textureCoord[] = {
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		};
		createVbo(textureVbo, textureCoord, sizeof(textureCoord));

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		ebo.init(indices, sizeof(indices));

		vao.unbind();
		ebo.unbind();
	}

	Sprite::~Sprite()
	{}

	void Sprite::render(const glm::vec2& position, 
						const glm::vec2& size, 
						const float rotation) const
	{
		glm::mat4 modelMat(1.0f);

		modelMat = glm::translate(modelMat, glm::vec3(position, 0.0f));
		modelMat = glm::translate(modelMat, glm::vec3(0.5f * size, 0.0f));
		modelMat = glm::rotate(modelMat, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::translate(modelMat, glm::vec3(-0.5f * size, 0.0f));
		modelMat = glm::scale(modelMat, glm::vec3(size, 1.0f));

		shaderProgram->use();
		shaderProgram->setMatrix4("modelMat", modelMat);

		glActiveTexture(GL_TEXTURE0);
		if (texture != nullptr)
			texture->bind();
		else if (textureAtlas != nullptr)
			textureAtlas->bind();

		Renderer::draw(vao, ebo, shaderProgram);
	}

	void Sprite::createVbo(VBO& vbo, const void* data, const size_t size)
	{
		vbo.init(data, size);

		VboLayout layout;
		layout.addElementFloat(2, false);
		vao.addBuffer(vbo, layout);
	}
}