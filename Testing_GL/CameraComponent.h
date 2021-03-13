#include <glm/glm.hpp>

struct Camera_Features
{
	GLfloat YAW = -90.0f;
	GLfloat PITCH = 0.0f;
	GLfloat SPEED = 6.0f;
	GLfloat SENSTIVITY = 0.15f;
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
	glm::vec3 WorldPosition = glm::vec3(0.0f);
	glm::vec3 LocalPosition = glm::vec3(0.0f);
	glm::vec3 Up = this->camera_features->WorldUp;
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 right = glm::cross(this->forward, this->camera_features->WorldUp);

public:

	CameraComponent()
	{
		this->UpdateCameraVectors();
	}

	void SetWorldPosition(glm::vec3 WorldPosition) { this->WorldPosition = WorldPosition; }
	void SetLocalPosition(glm::vec3 LocalPosition) { this->LocalPosition = LocalPosition; }
	void SetWorldRotation(glm::vec2 WorldRotation)
	{
		this->camera_features->YAW = WorldRotation.y;
		this->camera_features->PITCH = WorldRotation.x;
	}
	glm::vec3 GetWorldPosition() { return this->WorldPosition; }
	glm::vec3 GetLocalPosition() { return this->LocalPosition; }
	glm::vec3 GetForwardVector() { return this->forward; }
	glm::vec3 GetRightVector() { return this->right; }
	GLfloat GetCameraZoom() { return this->camera_features->ZOOM; }
	void SetForwardVector(glm::vec3 forward) { this->forward = forward; }
	
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(this->WorldPosition + this->LocalPosition, this->WorldPosition + this->LocalPosition + this->forward, this->Up);
	}
	
	void UpdateCameraVectors();
	void ProcessKeyBoardMovement(Movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch);
	void ProcessMouseScroll(GLfloat scrollOffset);
	void ProcessMovement(GLfloat DeltaTime, GLFWwindow* window);
};

void CameraComponent::UpdateCameraVectors()
{
	glm::vec3 forward = glm::vec3(1.0f);
	forward.x = cos(glm::radians(this->camera_features->YAW)) * cos(glm::radians(this->camera_features->PITCH));
	forward.y = sin(glm::radians(this->camera_features->PITCH));
	forward.z = sin(glm::radians(this->camera_features->YAW)) * cos(glm::radians(this->camera_features->PITCH));

	this->forward = glm::normalize(forward);
	this->right = glm::normalize(glm::cross(this->forward, this->camera_features->WorldUp));
	this->Up = glm::normalize(glm::cross(this->right, this->forward));
}

void CameraComponent::ProcessKeyBoardMovement(Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = camera_features->SPEED * deltaTime;
	if (Movement::FORWARD == direction)
	{
		this->WorldPosition += this->forward * velocity;
	}

	if (Movement::BACKWARD == direction)
	{
		this->WorldPosition -= this->forward * velocity;
	}

	if (Movement::RIGHT == direction)
	{
		this->WorldPosition += this->right * velocity;
	}

	if (Movement::LEFT == direction)
	{
		this->WorldPosition -= this->right * velocity;
	}
}

void CameraComponent::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
{
	if (bActivateInCursor)
	{
		xOffset *= this->camera_features->SENSTIVITY;
		yOffset *= this->camera_features->SENSTIVITY;

		this->camera_features->YAW -= xOffset;
		this->camera_features->PITCH -= yOffset;

		if (constrainPitch)
		{
			if (this->camera_features->PITCH > 89.0f) { this->camera_features->PITCH = 89.0f; }
			if (this->camera_features->PITCH < -89.0f) { this->camera_features->PITCH = -89.0f; }
		}

		this->UpdateCameraVectors();
	}

}

void CameraComponent::ProcessMouseScroll(GLfloat scrollOffset)
{
	if(bActivateInCursor)
	{
		if (this->camera_features->ZOOM >= 1.0f && this->camera_features->ZOOM <= 45.0f) { this->camera_features->ZOOM -= scrollOffset; }

		if (this->camera_features->ZOOM <= 1.0f) { this->camera_features->ZOOM = 1.0f; }

		if (this->camera_features->ZOOM >= 45.0f) { this->camera_features->ZOOM = 45.0f; }
	}

}


void CameraComponent::ProcessMovement(GLfloat DeltaTime,GLFWwindow* window)
{

	if (bActivateInCursor)
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


}
