#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int windowSizeX = 640;
int windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow *win, int w, int h);
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode);

int main()
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
    GLFWwindow *window = glfwCreateWindow(windowSizeX, windowSizeY, "Game", nullptr, nullptr);
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
	glClearColor(0, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/* Window size change handler */
void glfwWindowSizeCallback(GLFWwindow* win, int w, int h)
{
    windowSizeX = w;
    windowSizeY = h;
    glViewport(0, 0, windowSizeX, windowSizeY);
}

/* Key pressing handler */
void glfwKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GL_TRUE);
}