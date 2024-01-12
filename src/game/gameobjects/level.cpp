#include "level.h"

Level::Level(const std::vector<std::string> description)
	: width(description[0].length())
	, height(description.size())
{
	if (description.empty())
	{
		std::cerr << "ERROR::Emry level description!" << std::endl;
		return;
	}

	objects.reserve(width * height);

	unsigned int currentBottomOffset = BLOCK_SIZE * (height - 1);
	for (const std::string& row : description)
	{
		unsigned int currentLeftOffset = 0;

		for (const char element : row)
		{
			objects.emplace_back(createObjectFromDecription(element, 
															glm::vec2(currentLeftOffset, currentBottomOffset),
															glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 
															0.0f));

			currentLeftOffset += BLOCK_SIZE;
		}

		currentBottomOffset -= BLOCK_SIZE;
	}
}

std::shared_ptr<BrickWall> Level::createObjectFromDecription(const char description,
															  const glm::vec2& position, 
															  const glm::vec2& size, 
															  const float rotation)
{
	switch (description)
	{
	case '0':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_Right"), position, size, rotation);

	case '1':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_Bottom"), position, size, rotation);

	case '2':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_Left"), position, size, rotation);

	case '3':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_Top"), position, size, rotation);

	case '4':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall"), position, size, rotation);

	case '5':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BetonWall_Right"), position, size, rotation);

	case '6':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BetonWall_Bottom"), position, size, rotation);

	case '7':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BetonWall_Left"), position, size, rotation);

	case '8':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BetonWall_Top"), position, size, rotation);

	case '9':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BetonWall"), position, size, rotation);

	case 'A':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("Water1"), position, size, rotation);

	case 'B':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("Trees"), position, size, rotation);

	case 'C':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("Ice"), position, size, rotation);

	case 'D':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("Nothing"), position, size, rotation);

	case 'E':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("Eagle"), position, size, rotation);

	case 'F':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("Wall"), position, size, rotation);

	case 'G':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_BottomLeft"), position, size, rotation);

	case 'H':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_BottomRight"), position, size, rotation);

	case 'I':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_TopLeft"), position, size, rotation);

	case 'J':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("BrickWall_TopRight"), position, size, rotation);

	default:
		std::cerr << "ERROR::Unknown description: " << description << std::endl;
		return nullptr;
	}
}

void Level::render() const
{
	for (const auto& object : objects)
	{
		if (object != nullptr)
			object->render();
	}
}

void Level::update(const uint64_t delta)
{
	for (const auto& object : objects)
	{
		if (object != nullptr)
			object->update(delta);
	}
}
