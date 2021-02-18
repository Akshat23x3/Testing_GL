#include <glm/glm.hpp>

class CameraComponent
{
protected:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -3.0f);

public:
	void SetPosition(glm::vec3 position) { this->position = position; }
	void SetDirection(glm::vec3 direction) { this->direction = direction; }
	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetDirection() { return direction; }
};