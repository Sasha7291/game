#include "animatedsprite.h"

namespace RenderEngine
{
	AnimatedSprite::AnimatedSprite(const std::shared_ptr<TextureAtlas> textureAtlas,
								   const std::shared_ptr<ShaderProgram> shaderProgram,
								   const std::string& initialSubTexture)
		: Sprite(textureAtlas, shaderProgram, initialSubTexture)
		, currentFrame(0)
		, currentAnimationTime(0)
		, dirty(false)
	{
		currentAnimationDurations = states.end();
	}

	void AnimatedSprite::insertState(const std::string& name, const std::vector<State>& subTectureDuration)
	{
		states.emplace(name, subTectureDuration);
	}

	void AnimatedSprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation) const
	{
		if (dirty)
		{
			auto& subTexture = textureAtlas->getSubTexture(currentAnimationDurations->second[currentFrame].first);

			const GLfloat textureCoord[] = {
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y
			};

			textureVbo.update(textureCoord, sizeof(GLfloat) * 8);
			textureVbo.unbind();

			dirty = false;
		}

		Sprite::render(position, size, rotation);
	}

	void AnimatedSprite::setState(const std::string& name)
	{
		auto it = states.find(name);

		if (it == states.end())
		{
			std::cerr << "ERROR::Animation state " << name << " wasn't found!" << std::endl;
			return;
		}

		if (it != currentAnimationDurations)
		{
			currentFrame = 0;
			currentAnimationTime = 0;
			currentAnimationDurations = it;
			dirty = true;
		}
	}

	void AnimatedSprite::update(const uint64_t delta)
	{
		if (currentAnimationDurations != states.end())
		{
			currentAnimationTime += delta;

			while (currentAnimationTime >= currentAnimationDurations->second[currentFrame].second)
			{
				currentAnimationTime -= currentAnimationDurations->second[currentFrame].second;
				++currentFrame;
				dirty = true;

				if (currentFrame == currentAnimationDurations->second.size())
					currentFrame = 0;
			}
		}
	}
}