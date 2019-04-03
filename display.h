#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display
{
	public:
		Display(int width, int height, const std::string& title);

		void Clear(float red, float green, float blue, float alpha);
		void Update();
		bool IsClosed();
		void ProcessInput();
		
		GLFWwindow* GetWindow() { return window; }

		virtual ~Display();
		
	private:
	  GLFWwindow *window;
};

#endif