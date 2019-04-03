#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		projection = glm::perspective(fov, aspect, zNear, zFar);
		position = pos;

		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 GetViewProjection() const { return projection * glm::lookAt(position, position + forward, up); }

	virtual ~Camera()
	{}
	
private:
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif