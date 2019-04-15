#include "display.h"


Display::Display(int width, int height, const std::string &title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		Display::~Display();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		Display::~Display();
	}

	// tell OpenGL the size of the rendering window
	glViewport(0, 0, width, height);
	// handle window resizing
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glCullFace(GL_BACK);

	// fix mac bug
	int x, y;
	glfwGetWindowPos(window, &x, &y);
	glfwSetWindowPos(window, x++, y++);
	Update();
	glfwSetWindowPos(window, x--, y--);
	Update();

}

Display::~Display()
{}

void Display::Clear(float red, float green, float blue, float alpha)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::EnableCullFace()
{
	glEnable(GL_CULL_FACE);
}

void Display::DisableCullFace()
{
	glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
}

void Display::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}


bool Display::IsClosed()
{
	return glfwWindowShouldClose(window); 
}

void Display::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
