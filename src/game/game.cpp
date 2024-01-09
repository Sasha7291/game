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
    auto spriteShaderProgram = ResourceManager::loadShaderProgram("SpriteShader", "res/shaders/sprite.vert", "res/shaders/sprite.frag");
    if (spriteShaderProgram == nullptr)
    {
        std::cerr << "ERROR::Shader wasn't created!" << std::endl;
        return false;
    }

    std::vector<std::string> subTextureNames = {
        "block",
        "topBlock",
        "bottomBlock",
        "leftBlock",
        "rightBlock",
        "topLeftBlock",
        "topRightBlock",
        "bottomLeftBlock",
        "bottomRightBlock"
    };

    auto textureAtlas = ResourceManager::loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTextureNames), 8, 8);
    auto animatedSprite = ResourceManager::loadAnimatedSprite("AnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "block");
    std::vector<std::pair<std::string, uint64_t>> state1;
    state1.emplace_back(std::make_pair<std::string, uint64_t>("block", 1000000000));
    state1.emplace_back(std::make_pair<std::string, uint64_t>("topBlock", 1000000000));
    state1.emplace_back(std::make_pair<std::string, uint64_t>("bottomBlock", 1000000000));
    std::vector<std::pair<std::string, uint64_t>> state2;
    state2.emplace_back(std::make_pair<std::string, uint64_t>("block", 1000000000));
    state2.emplace_back(std::make_pair<std::string, uint64_t>("leftBlock", 1000000000));
    state2.emplace_back(std::make_pair<std::string, uint64_t>("rightBlock", 1000000000));

    animatedSprite->insertState("state1", state1);
    animatedSprite->insertState("state2", state2);

    animatedSprite->setState("state2");
    animatedSprite->setPosition(glm::vec2(300, 300));

    glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y), -100.0f, 100.0f);

    spriteShaderProgram->use();
    spriteShaderProgram->setInt("tex", 0);
    spriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    std::vector<std::string> tanksSubTextureNames = {
        "tankTop1",
        "tankTop2",
        "tankLeft1",
        "tankLeft2",
        "tankBottom1",
        "tankBottom2",
        "tankRight1",
        "tankRight2"
    };

    auto tankTextureAtlas = ResourceManager::loadTextureAtlas("TankTextureAtlas", "res/textures/tanks.png", std::move(tanksSubTextureNames), 16, 16);
    auto tankAnimatedSprite = ResourceManager::loadAnimatedSprite("TankTextureSprite", "TankTextureAtlas", "SpriteShader", 100, 100, "tankTop1");
    std::vector<std::pair<std::string, uint64_t>> tankTopState;
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop1", 500000000));
    tankTopState.emplace_back(std::make_pair<std::string, uint64_t>("tankTop2", 500000000));
    std::vector<std::pair<std::string, uint64_t>> tankBottomState;
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom1", 500000000));
    tankBottomState.emplace_back(std::make_pair<std::string, uint64_t>("tankBottom2", 500000000));
    std::vector<std::pair<std::string, uint64_t>> tankRightState;
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight1", 500000000));
    tankRightState.emplace_back(std::make_pair<std::string, uint64_t>("tankRight2", 500000000));
    std::vector<std::pair<std::string, uint64_t>> tankLeftState;
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft1", 500000000));
    tankLeftState.emplace_back(std::make_pair<std::string, uint64_t>("tankLeft2", 500000000));

    tankAnimatedSprite->insertState("tankTopState", tankTopState);
    tankAnimatedSprite->insertState("tankBottomState", tankBottomState);
    tankAnimatedSprite->insertState("tankLeftState", tankLeftState);
    tankAnimatedSprite->insertState("tankRightState", tankRightState);

    tankAnimatedSprite->setState("tankTopState");

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
