#pragma once

#include "../src/resources/resourcemanager.h"
#include "brickwall.h"

class Level
{
public:
	explicit Level(const std::vector<std::string> description);

	std::shared_ptr<BrickWall> createObjectFromDecription(const char description,
														   const glm::vec2& position, 
														   const glm::vec2& size, 
														   const float rotation);
	void render() const;
	void update(const uint64_t delta);

private:
	size_t width;
	size_t height;
	std::vector<std::shared_ptr<GameObject>> objects;

	const unsigned int BLOCK_SIZE = 16u;
};