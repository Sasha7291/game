#include "sprite.h"

namespace RenderEngine
{
	Sprite::Sprite(const std::shared_ptr<Texture2d> texture, 
		    	   const std::string& initialSubTexture,
				   const std::shared_ptr<ShaderProgram> shaderProgram, 
				   const glm::vec2& position, 
				   const glm::vec2& size, 
				   const float rotationAngle)
		: texture(texture)
		, shaderProgram(shaderProgram)
		, position(position)
		, size(size)
		, rotationAngle(rotationAngle)
		, vao()
		, textureVbo()
		, vertexVbo()
		, ebo()
	{
		const GLfloat vertexCoord[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
		};

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		auto& subTexture = this->texture->getSubTexture(initialSubTexture);

		const GLfloat textureCoord[] = {
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		};

		vertexVbo.init(vertexCoord, static_cast<unsigned long long int>(2) * 4 * sizeof(GLfloat));
		VboLayout vertexLayout;
		vertexLayout.addElementFloat(2, false);
		vao.addBuffer(vertexVbo, vertexLayout);

		textureVbo.init(textureCoord, static_cast<unsigned long long int>(2) * 4 * sizeof(GLfloat));
		VboLayout textureLayout;
		textureLayout.addElementFloat(2, false);
		vao.addBuffer(textureVbo, textureLayout);

		ebo.init(indices, 6);

		vao.unbind();
		ebo.unbind();
	}

	Sprite::~Sprite()
	{}

	void Sprite::render() const
	{
		shaderProgram->use();

		glm::mat4 modelMat(1.0f);

		modelMat = glm::translate(modelMat, glm::vec3(position, 1.0f));
		modelMat = glm::translate(modelMat, glm::vec3(0.5f * size, 1.0f));
		modelMat = glm::rotate(modelMat, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::translate(modelMat, glm::vec3(-0.5f * size, 1.0f));
		modelMat = glm::scale(modelMat, glm::vec3(size, 1.0f));

		shaderProgram->setMatrix4("modelMat", modelMat);
		glActiveTexture(GL_TEXTURE0);
		texture->bind();

		Renderer::draw(vao, ebo, *shaderProgram);
	}

	void Sprite::setPosition(const glm::vec2& position)
	{
		this->position = position;
	}

	void Sprite::setRotation(const float rotationAngle)
	{
		this->rotationAngle = rotationAngle;
	}

	void Sprite::setSize(const glm::vec2& size)
	{
		this->size = size;
	}
}