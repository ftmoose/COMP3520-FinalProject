#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& in_pos = glm::vec3(), const glm::vec3& in_rot = glm::vec3(), const glm::vec3& in_scale = glm::vec3(1.0f)):
		pos(in_pos), rot(in_rot), scale(in_scale)
	{}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(pos);

		glm::mat4 rotXMatrix = glm::rotate(glm::radians(rot.x), glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(glm::radians(rot.y), glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(glm::radians(rot.z), glm::vec3(0, 0, 1));

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		glm::mat4 scaleMatrix = glm::scale(scale);

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPos() { return pos; }
	inline glm::vec3& GetRot() { return rot; }
	inline glm::vec3& GetScale() { return scale; }

	inline void SetPos(glm::vec3 in_pos) { pos = in_pos; }
	inline void SetRot(glm::vec3 in_rot) { rot = in_rot; }
	inline void SetScale(glm::vec3 in_scale) { scale = in_scale; }

	virtual ~Transform()
	{}

private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};

#endif