#pragma once

#include "../src/renderer/animatedsprite.h"

class GameObject
{
public:
	explicit GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual ~GameObject();

	virtual void render() const = 0;
	virtual void update(const uint64_t delta) = 0;

protected:
	glm::vec2 position;
	glm::vec2 size;
	float rotation;

};