#pragma once

#include "sprite.h"

#include <vector>

namespace RenderEngine
{
	class AnimatedSprite : public Sprite
	{
	private:
		typedef std::pair<std::string, uint64_t> State;
		typedef std::map<std::string, std::vector<State>> StatesMap;

	public:
		explicit AnimatedSprite(const std::shared_ptr<TextureAtlas> texture,
								const std::shared_ptr<ShaderProgram> shaderProgram,
								const std::string& initialSubTexture);

		void insertState(const std::string& name, const std::vector<State>& subTectureDuration);
		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
		void setState(const std::string& name);
		void update(const uint64_t delta);

	private:
		StatesMap states;
		StatesMap::const_iterator currentAnimationDurations;

		size_t currentFrame; 
		uint64_t currentAnimationTime; 
		mutable bool dirty; 

	};
}