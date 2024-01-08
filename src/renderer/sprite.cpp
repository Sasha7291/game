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
		, textureVbo(0)
		, vertexVbo(0)
	{
		const GLfloat vertexCoord[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,

			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f
		};

		auto& subTexture = texture->getSubTexture(initialSubTexture);

		const GLfloat textureCoord[] = {
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,

			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vertexVbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoord), &vertexCoord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &textureVbo);
		glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoord), &textureCoord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &vertexVbo);
		glDeleteBuffers(1, &textureVbo);
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
		glDrawArrays(GL_TRIANGLES, 0, 6);

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