#pragma once

#include "gameobject.h"

class BrickWall final : public GameObject
{
public:
	explicit BrickWall(const std::shared_ptr<RenderEngine::Sprite> sprite,
					   const glm::vec2& position,
					   const glm::vec2& size,
					   const float rotation);
	~BrickWall();

	void render() const override;
	void update(const uint64_t delta) override;

private:
	std::shared_ptr<RenderEngine::Sprite> sprite;

};