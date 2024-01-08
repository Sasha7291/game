#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "resources/resourcemanager.h"

glm::ivec2 windowSize(640, 480);

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
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
    /* Set clear color */
	glClearColor(0, 0, 0, 1);

    {
        ResourceManager manager(argv[0]);

        auto spriteShaderProgram = manager.loadShaderProgram("SpriteShader", "res/shaders/sprite.vert", "res/shaders/sprite.frag");
        if (spriteShaderProgram == nullptr)
        {
            std::cerr << "ERROR::Shader wasn't created!" << std::endl;
            return -1;
        }

        std::vector<std::string> subTextureNames = { "block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock" };

        auto texture = manager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");
        auto textureAtlas = manager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTextureNames), 8, 8);
        auto sprite = manager.loadSprite("Sprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "block");
        sprite->setPosition(glm::vec2(100, 100));

        glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y), -100.0f, 100.0f);

        spriteShaderProgram->use();
        spriteShaderProgram->setInt("tex", 0);
        spriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Drawing */
            sprite->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

/* Window size change handler */
void glfwWindowSizeCallback(GLFWwindow* win, int w, int h)
{
    windowSize.x = w;
    windowSize.y = h;
    glViewport(0, 0, windowSize.x, windowSize.y);
}

/* Key pressing handler */
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GL_TRUE);
}