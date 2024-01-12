#include "brickwall.h"

BrickWall::BrickWall(const std::shared_ptr<RenderEngine::Sprite> sprite, 
					 const glm::vec2& position, 
					 const glm::vec2& size, 
					 const float rotation)
	: GameObject(position, size, rotation)
	, sprite(sprite)
{
}

BrickWall::~BrickWall()
{
}

void BrickWall::render() const
{
	sprite->render(position, size, rotation);
}

void BrickWall::update(const uint64_t delta)
{
}
