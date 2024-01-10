#include "animatedsprite.h"

namespace RenderEngine
{
	AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture2d> texture, 
								   const std::string& initialSubTexture, 
								   const std::shared_ptr<ShaderProgram> shaderProgram, 
								   const glm::vec2& position, 
								   const glm::vec2& size, 
								   const float rotationAngle)
	: Sprite(texture, initialSubTexture, shaderProgram, position, size, rotationAngle)
	{
		currentAnimationDurations = statesMap.end();
	}

	void AnimatedSprite::insertState(const std::string& name, const std::vector<std::pair<std::string, uint64_t>>& subTectureDuration)
	{
		statesMap.emplace(name, subTectureDuration);
	}

	void AnimatedSprite::render() const
	{
		if (dirty)
		{
			auto& subTexture = texture->getSubTexture(currentAnimationDurations->second[currentFrame].first);

			const GLfloat textureCoord[] = {
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y
			};

			textureVbo.update(textureCoord, static_cast<unsigned long long>(2) * 4 * sizeof(GLfloat));
			textureVbo.unbind();

			dirty = false;
		}

		Sprite::render();
	}

	void AnimatedSprite::setState(const std::string& name)
	{
		auto it = statesMap.find(name);

		if (it == statesMap.end())
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
		if (currentAnimationDurations != statesMap.end())
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