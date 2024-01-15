#pragma once

#include "renderer.h"
#include "shaderprogram.h"
#include "textureatlas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <array>
#include <memory>

namespace RenderEngine 
{
	class Sprite
	{
	public:
		Sprite(const std::shared_ptr<Texture2d> texture,
			   const std::shared_ptr<ShaderProgram> shaderProgram);
		Sprite(const std::shared_ptr<TextureAtlas> textureAtlas,
			   const std::shared_ptr<ShaderProgram> shaderProgram,
			   const std::string& initialSubTexture);

		~Sprite();

		virtual void render(const glm::vec2& position, 
							const glm::vec2& size, 
							const float rotation) const;
		
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

	protected:
		std::shared_ptr<Texture2d> texture; 
		std::shared_ptr<TextureAtlas> textureAtlas;
		std::shared_ptr<ShaderProgram> shaderProgram;
		VAO vao; 
		VBO vertexVbo; 
		VBO textureVbo;
		EBO ebo;

	private:
		void createVbo(VBO& vbo, const void* data, const size_t size);

	};
}