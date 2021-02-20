#include <glm/glm.hpp>

struct Camera_Features
{
	GLfloat YAW = -90.0f;
	GLfloat PITCH = 0.0f;
	GLfloat SPEED = 6.0f;
	GLfloat SENSTIVITY = 0.25f;
	GLfloat ZOOM = 45.0f;
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

enum Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class CameraComponent
{
protected:
	Camera_Features* camera_features = new Camera_Features();
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Up = this->camera_features->WorldUp;
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 right = glm::cross(this->forward, this->camera_features->WorldUp);

public:
	void SetPosition(glm::vec3 position) { this->position = position; }
	glm::vec3 GetPosition() { return this->position; }
	glm::vec3 GetForwardVector() { return this->forward; }
	glm::vec3 GetRightVector() { return this->right; }
	GLfloat GetCameraZoom() { return this->camera_features->ZOOM; }
	
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->position, this->position + this->forward, this->Up);
	}
	
	void UpdateCameraVectors();
	void ProcessKeyBoardMovement(Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch);
	void ProcessMouseScroll(GLfloat scrollOffset);
	void ProcessMovement(GLfloat DeltaTime);
};

void CameraComponent::UpdateCameraVectors()
{
	glm::vec3 forward = glm::vec3(1.0f);
	forward.x = cos(glm::radians(this->camera_features->YAW)) * cos(glm::radians(this->camera_features->PITCH));
	forward.y = sin(glm::radians(this->camera_features->PITCH));
	forward.z = sin(glm::radians(this->camera_features->YAW)) * cos(glm::radians(this->camera_features->PITCH));

	this->forward = glm::normalize(forward);
	this->right = glm::normalize(glm::cross(this->forward, this->camera_features->WorldUp));
	this->Up = glm::normalize(glm::cross(this->forward, this->right));
}

void CameraComponent::ProcessKeyBoardMovement(Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = camera_features->SPEED * deltaTime;
	if (Movement::FORWARD == direction)
	{
		this->position += this->forward * velocity;
	}

	if (Movement::BACKWARD == direction)
	{
		this->position -= this->forward * velocity;
	}

	if (Movement::RIGHT == direction)
	{
		this->position += glm::cross(this->forward, this->Up) * velocity;
	}

	if (Movement::LEFT == direction)
	{
		this->position -= glm::cross(this->forward, this->Up) * velocity;
	}
}

void CameraComponent::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
{
	xOffset *= this->camera_features->SENSTIVITY;
	yOffset *= this->camera_features->SENSTIVITY;

	this->camera_features->YAW += xOffset;
	this->camera_features->PITCH += yOffset;

	if (constrainPitch)
	{
		if (this->camera_features->PITCH > 89.0f) { this->camera_features->PITCH = 89.0f; }
		if (this->camera_features->PITCH < -89.0f) { this->camera_features->PITCH = -89.0f; }
	}

	this->UpdateCameraVectors();
}

void CameraComponent::ProcessMouseScroll(GLfloat scrollOffset)
{
	if (this->camera_features->ZOOM >= 1.0f && this->camera_features->ZOOM <= 45.0f){ this->camera_features->ZOOM -= scrollOffset; }

	if (this->camera_features->ZOOM <= 1.0f){ this->camera_features->ZOOM = 1.0f; }

	if (this->camera_features->ZOOM >= 45.0f) { this->camera_features->ZOOM = 45.0f; }
}


void CameraComponent::ProcessMovement(GLfloat DeltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		this->ProcessKeyBoardMovement(Movement::FORWARD, DeltaTime);
	}	
	if (keys[GLFW_KEY_S])
	{
		this->ProcessKeyBoardMovement(Movement::BACKWARD, DeltaTime);
	}	
	if (keys[GLFW_KEY_A])
	{
		this->ProcessKeyBoardMovement(Movement::LEFT, DeltaTime);
	}	
	if (keys[GLFW_KEY_D])
	{
		this->ProcessKeyBoardMovement(Movement::RIGHT, DeltaTime);
	}

}
