#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "renderer/shaderprogram.h"

GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertexShader =
    "#version 460\n"
    "layout(location = 0) in vec3 vertex_position;"
    "layout(location = 1) in vec3 vertex_color;"
    "out vec3 color;"
    "void main()"
    "{"
    "   color = vertex_color;"
    "   gl_Position = vec4(vertex_position, 1.0);"
    "}";

const char* fragmentShader =
    "#version 460\n"
    "in vec3 color;"
    "out vec4 frag_color;"
    "void main()"
    "{"
    "   frag_color = vec4(color, 1.0);"
    "}";

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
    GLFWwindow* window = glfwCreateWindow(windowSizeX, windowSizeY, "Game", nullptr, nullptr);
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

    std::string vs(vertexShader);
    std::string fs(fragmentShader);
    Renderer::ShaderProgram shaderProgram(vs, fs);
    if (!shaderProgram.isCompiled())
    {
        std::cerr << "Shader wasn't created!" << std::endl;
        return -1;
    }

    /* Buffer generating */
    GLuint pointsVbo = 0;
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colorsVbo = 0;
    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Drawing */
        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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