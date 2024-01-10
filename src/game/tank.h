#pragma once

#include "../src/renderer/animatedsprite.h"

class Tank
{
public:
	enum class Orientation
	{
		Top,
		Bottom,
		Left,
		Right
	};

	explicit Tank(std::shared_ptr<RenderEngine::AnimatedSprite> sprite,
				  const float velocity,
				  const glm::vec2& position);

	void move(const bool move);
	void render() const;
	void setOrientation(Orientation orientation);
	void update(const uint64_t delta);

private:
	Orientation orientation;
	std::shared_ptr<RenderEngine::AnimatedSprite> sprite;
	glm::vec2 position;
	glm::vec2 moveOffset;
	float velocity;
	bool moving;
	
};