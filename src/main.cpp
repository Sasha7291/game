#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

#include "resources/resourcemanager.h"

GLfloat points[] = {
    0.0f, 50.0f, 0.0f,
    50.0f, -50.0f, 0.0f,
    -50.0f, -50.0f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat tex[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
};

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
        auto defaultShaderProgram = manager.loadShaderProgram("DefaultShader", "res/shaders/shader2d.vert", "res/shaders/shader2d.frag");
        if (defaultShaderProgram == nullptr)
        {
            std::cerr << "ERROR::Shader wasn't created!" << std::endl;
            return -1;
        }

        auto spriteShaderProgram = manager.loadShaderProgram("SpriteShader", "res/shaders/sprite.vert", "res/shaders/sprite.frag");
        if (spriteShaderProgram == nullptr)
        {
            std::cerr << "ERROR::Shader wasn't created!" << std::endl;
            return -1;
        }

        auto texture = manager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

        std::vector<std::string> subTextureNames = { "block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock"};

        auto textureAtlas = manager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTextureNames), 8, 8);

        auto sprite = manager.loadSprite("Sprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "block");
        sprite->setPosition(glm::vec2(300, 100));

        /* Buffer generating */
        GLuint pointsVbo = 0;
        glGenBuffers(1, &pointsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colorsVbo = 0;
        glGenBuffers(1, &colorsVbo);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint textureVbo = 0;
        glGenBuffers(1, &textureVbo);
        glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex), tex, GL_STATIC_DRAW);

        /* Creating vertex array */
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        defaultShaderProgram->use();
        defaultShaderProgram->setInt("tex", 0);

        glm::mat4 modelMatrix1 = glm::mat4(1.0f);
        modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(100.0f, 200.0f, 0.0f));

        glm::mat4 modelMatrix2 = glm::mat4(1.0f);
        modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(590.0f, 200.0f, 0.0f));

        glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y), -100.0f, 100.0f);

        defaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        spriteShaderProgram->use();
        spriteShaderProgram->setInt("tex", 0);
        spriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Drawing */
            defaultShaderProgram->use();
            glBindVertexArray(vao);
            texture->bind();

            defaultShaderProgram->setMatrix4("modelMat", modelMatrix1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            defaultShaderProgram->setMatrix4("modelMat", modelMatrix2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

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