#include "gameobject.h"

GameObject::GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation)
	: position(position)
	, size(size)
	, rotation(rotation)
{}

GameObject::~GameObject()
{}
