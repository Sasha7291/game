#include "tank.h"

Tank::Tank(std::shared_ptr<RenderEngine::AnimatedSprite> sprite, const float velocity, const glm::vec2& position, const glm::vec2& size)
	: GameObject(position, size, 0.0f)
	, orientation(Orientation::Top)
	, sprite(sprite)
	, moveOffset(glm::vec2(0.0f, 1.0f))
	, velocity(velocity)
	, moving(false) 
{}

void Tank::move(const bool move)
{
	moving = move;
}

void Tank::render() const
{
	sprite->render(position, size, rotation);
}

void Tank::setOrientation(Orientation orientation)
{
	if (this->orientation == orientation)
		return;

	this->orientation = orientation;

	switch (orientation)
	{
	case Tank::Orientation::Top:
		sprite->setState("TankTopState");
		moveOffset.x = 0.0f;
		moveOffset.y = 1.0f;
		break;

	case Tank::Orientation::Bottom:
		sprite->setState("TankBottomState");
		moveOffset.x = 0.0f;
		moveOffset.y = -1.0f;
		break;

	case Tank::Orientation::Left:
		sprite->setState("TankLeftState");
		moveOffset.x = -1.0f;
		moveOffset.y = 0.0f;
		break;

	case Tank::Orientation::Right:
		sprite->setState("TankRightState");
		moveOffset.x = 1.0f;
		moveOffset.y = 0.0f;
		break;

	default:
		break;
	}
}

void Tank::update(const uint64_t delta)
{
	if (moving)
	{
		position += delta * velocity * moveOffset;
		sprite->update(delta);
	}
}
