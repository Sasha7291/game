#include "sprite.h"

namespace Renderer
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
		, vao(0)
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

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vertexVbo.init(vertexCoord, static_cast<unsigned long long int>(2) * 4 * sizeof(GLfloat));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		textureVbo.init(textureCoord, static_cast<unsigned long long int>(2) * 4 * sizeof(GLfloat));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		ebo.init(indices, static_cast<unsigned long long int>(6) * sizeof(GLuint));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Sprite::~Sprite()
	{
		glDeleteVertexArrays(1, &vao);
	}

	void Sprite::render() const
	{
		shaderProgram->use();

		glm::mat4 modelMat(1.0f);

		modelMat = glm::translate(modelMat, glm::vec3(position, 1.0f));
		modelMat = glm::translate(modelMat, glm::vec3(0.5f * size, 1.0f));
		modelMat = glm::rotate(modelMat, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::translate(modelMat, glm::vec3(-0.5f * size, 1.0f));
		modelMat = glm::scale(modelMat, glm::vec3(size, 1.0f));

		glBindVertexArray(vao);
		shaderProgram->setMatrix4("modelMat", modelMat);
		glActiveTexture(GL_TEXTURE0);
		texture->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
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