#include "tank.h"

Tank::Tank(std::shared_ptr<Renderer::AnimatedSprite> sprite, const float velocity, const glm::vec2& position)
	: orientation(Orientation::Top)
	, sprite(sprite)
	, position(position)
	, moveOffset(glm::vec2(0.0f, 1.0f))
	, velocity(velocity)
	, moving(false) 
{
	this->sprite->setPosition(this->position);
}

void Tank::move(const bool move)
{
	moving = move;
}

void Tank::render() const
{
	sprite->render();
}

void Tank::setOrientation(Orientation orientation)
{
	if (this->orientation == orientation)
		return;

	this->orientation = orientation;

	switch (orientation)
	{
	case Tank::Orientation::Top:
		sprite->setState("tankTopState");
		moveOffset.x = 0.0f;
		moveOffset.y = 1.0f;
		break;

	case Tank::Orientation::Bottom:
		sprite->setState("tankBottomState");
		moveOffset.x = 0.0f;
		moveOffset.y = -1.0f;
		break;

	case Tank::Orientation::Left:
		sprite->setState("tankLeftState");
		moveOffset.x = -1.0f;
		moveOffset.y = 0.0f;
		break;

	case Tank::Orientation::Right:
		sprite->setState("tankRightState");
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
		sprite->setPosition(position);
		sprite->update(delta);
	}
}
