#include "game.h"

Game::Game(const glm::ivec2& ws)
	: currentGameState(GameState::Active)
    , windowSize(ws)
{
	keys.fill(false);
}

Game::~Game()
{

}

bool Game::init()
{
    ResourceManager::loadJsonResources("res/resources.json");

    auto spriteShaderProgram = ResourceManager::getShaderProgram("SpriteShader");
    if (spriteShaderProgram == nullptr)
    {
        std::cerr << "ERROR::Shader wasn't created!" << std::endl;
        return false;
    }

    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y), -100.0f, 100.0f);

    spriteShaderProgram->use();
    spriteShaderProgram->setInt("tex", 0);
    spriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    auto tankAnimatedSprite = ResourceManager::getAnimatedSprite("TanksAnimatedSprite");

    tank = std::make_unique<Tank>(tankAnimatedSprite, 0.0000001f, glm::vec2(100, 100));

	return true;
}

void Game::render()
{
    //ResourceManager::getAnimatedSprite("AnimatedSprite")->render();
    if (tank != nullptr)
        tank->render();
}

void Game::setKey(const int key, const int action)
{
	keys[key] = action;
}

void Game::update(const uint64_t delta)
{
    //ResourceManager::getAnimatedSprite("AnimatedSprite")->update(delta);
    if (tank != nullptr)
    {
        if (keys[GLFW_KEY_W])
        {
            tank->setOrientation(Tank::Orientation::Top);
            tank->move(true);
        }
        else if (keys[GLFW_KEY_S])
        {
            tank->setOrientation(Tank::Orientation::Bottom);
            tank->move(true);
        }
        else if (keys[GLFW_KEY_A])
        {
            tank->setOrientation(Tank::Orientation::Left);
            tank->move(true);
        }
        else if (keys[GLFW_KEY_D])
        {
            tank->setOrientation(Tank::Orientation::Right);
            tank->move(true);
        }
        else
        {
            tank->move(false);
        }

        tank->update(delta);
    }
}
