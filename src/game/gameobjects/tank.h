#pragma once

#include "gameobject.h"

class Tank final : public GameObject
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
				  const glm::vec2& position, 
				  const glm::vec2& size);

	void move(const bool move);
	void render() const override;
	void setOrientation(Orientation orientation);
	void update(const uint64_t delta) override;

private:
	Orientation orientation;
	std::shared_ptr<RenderEngine::AnimatedSprite> sprite;
	glm::vec2 moveOffset;
	float velocity;
	bool moving;
	
};