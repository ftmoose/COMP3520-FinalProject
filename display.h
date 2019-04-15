#ifndef DISPLAY_H
#define DISPLAY_H

#include "camera.h"
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

		void EnableCullFace();
		void DisableCullFace();
		
		GLFWwindow* GetWindow() { return window; }

		virtual ~Display();
		
	private:
	  GLFWwindow *window;

};

#endif