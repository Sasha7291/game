#include "game/game.h"

#include <iostream>
#include <vector>
#include <chrono>

glm::ivec2 windowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> game = std::make_unique<Game>(windowSize);

void glfwWindowSizeCallback(GLFWwindow *win, int w, int h);
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode);

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Glfw didn't init" << std::endl;
        return -1;
    }

    /* Use the functions of current OpenGL version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(windowSize.x, windowSize.y, "Game", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Window wasn't created" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Registration handlers */
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
    /* GL initilize */
	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}
	
    /* Information about OpenGL version */
    std::cout << "Renderer: " << RenderEngine::Renderer::getRenderStr() << std::endl;
	std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << std::endl;
	
    /* Set clear color */
    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);

    {
        ResourceManager::setExecutablePath(argv[0]);

        game->init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Poll for and process events */
            glfwPollEvents();

            /* Drawing */
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            game->update(duration);

            RenderEngine::Renderer::clear();

            /* Render here */
            game->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

        game = nullptr;
        ResourceManager::unloadAllResources();
    }

    glfwTerminate();
    return 0;
}

/* Window size change handler */
void glfwWindowSizeCallback(GLFWwindow* win, int w, int h)
{
    windowSize.x = w;
    windowSize.y = h;
    

    const float mapAspectRatio = 13.0f / 14.0f;
    unsigned int viewPortWidth = windowSize.x;
    unsigned int viewPortHeight = windowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(windowSize.x) / windowSize.y > mapAspectRatio)
    {
        viewPortWidth = windowSize.y * mapAspectRatio;
        viewPortLeftOffset = (windowSize.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = windowSize.x / mapAspectRatio;
        viewPortBottomOffset = (windowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setViewport(viewPortLeftOffset, viewPortBottomOffset, viewPortWidth, viewPortHeight);
}

/* Key pressing handler */
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GL_TRUE);

    game->setKey(key, action);
}