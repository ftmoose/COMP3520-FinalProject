#ifndef CAMERA_H
#define CAMERA_H

#include <iostream> 
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Mouse
{
	float lastX;
	float lastY;
	float sensitivity;
	bool first;
	Mouse(float x, float y, float s):
		lastX(x), lastY(y), sensitivity(s), first(true)
	{}
};

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, GLFWwindow* window)
	{

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetWindowUserPointer(window, this);
		glfwSetCursorPosCallback(window, +[](GLFWwindow* win, double a, double b){
    		static_cast<Camera*>(glfwGetWindowUserPointer(win))->mouse_callback(win, a, b);
		});

		projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
		position = pos;
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const { return projection * glm::lookAt(position, position + forward, up); }


	void ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += speed * forward;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= speed * forward;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= glm::normalize(glm::cross(forward, up)) * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += glm::normalize(glm::cross(forward, up)) * speed;
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (mouse->first)
		{
			mouse->lastX = xpos;
			mouse->lastY = ypos;
			mouse->first = false;
		}

		float xoffset = xpos - mouse->lastX;
		float yoffset = mouse->lastY - ypos; 
		mouse->lastX = xpos;
		mouse->lastY = ypos;

		xoffset *= mouse->sensitivity;
		yoffset *= mouse->sensitivity;

		yaw   += xoffset;
    	pitch += yoffset;

		if(pitch > 89.0f)
        	pitch = 89.0f;
    	if(pitch < -89.0f)
        	pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward = glm::normalize(front);
	}

	virtual ~Camera()
	{}

	inline glm::vec3 GetPosition() { return position; }
	
private:
	float speed = 1.0f;
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

	float yaw = -90.0f;
	float pitch = 0.0f;

	Mouse* mouse = new Mouse(400.0f, 300.0f, 0.05f);
	
};

#endif