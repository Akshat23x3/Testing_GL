#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CameraComponent.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

CameraComponent* EngineCamera = new CameraComponent();

class Transformations
{

protected:
	glm::vec3 LocalPosition = glm::vec3(0.0f);
	glm::vec3 LocalRotation = glm::vec3(0.0f);
	glm::vec3 LocalScale = glm::vec3(0.0f);
	glm::vec3 WorldPosition = glm::vec3(0.0f);
	glm::vec3 WorldRotation = glm::vec3(0.0f);
	glm::vec3 WorldScale = glm::vec3(1);

	glm::mat4 projection = glm::perspective(glm::radians(EngineCamera->GetCameraZoom()), (GLfloat)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	void reset_matrices()
	{
		this->LocalPosition = glm::vec3(1.0f);
		this->WorldPosition = glm::vec3(1.0f); this->WorldScale = glm::vec3(1.0f); this->WorldRotation = glm::vec3(0.0f);
	}

public:
	Transformations()
	{
		glm::vec3 LocalPosition = glm::vec3(0.0f);
		glm::vec3 LocalRotation = glm::vec3(0.0f);
		glm::vec3 LocalScale = glm::vec3(0.0f);
		glm::vec3 WorldPosition = glm::vec3(0.0f);
		glm::vec3 WorldRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 WorldScale = glm::vec3(1.0);

		//glm::mat4 projection = glm::perspective(glm::radians(EngineCamera->GetCameraZoom()), (GLfloat)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	glm::mat4 Project_On_Screen()
	{
		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);

		model = glm::translate(model, this->WorldPosition + this->LocalPosition);
		model = glm::rotate(model, glm::radians(this->WorldRotation.x + this->LocalRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->WorldRotation.y + this->LocalRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->WorldRotation.z + this->LocalRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, this->WorldScale + this->LocalScale);

		view = EngineCamera->GetViewMatrix();

		return projection * view * model;
	}

	virtual void Set_WorldPosition(glm::vec3 WorldPosition) { this->WorldPosition = WorldPosition; }
	virtual void Set_WorldRotation(glm::vec3 WorldRotation) { this->WorldRotation = WorldRotation; }
	virtual void Set_WorldScale(glm::vec3 WorldScale) { this->WorldScale = WorldScale; }
	virtual void Set_LocalPosition(glm::vec3 LocalPosition) { this->LocalPosition = LocalPosition; }
	virtual void Set_LocalRotation(glm::vec3 LocalRotation) { this->LocalRotation = LocalRotation; }
	virtual void Set_LocalScale(glm::vec3 LocalScale) { this->LocalScale = LocalScale; }

	virtual glm::vec3 Get_WorldPosition() { return this->WorldPosition; }
	virtual glm::vec3 Get_WorldRotation() { return this->WorldRotation; }
	virtual glm::vec3 Get_WorldScale() { return this->WorldScale; }
	virtual glm::vec3 Get_LocalPosition() { return this->LocalPosition; }
	virtual glm::vec3 Get_LocalRotation() { return this->LocalRotation; }
	virtual glm::vec3 Get_LocalScale() { return this->LocalScale; } 
	virtual glm::mat4 Get_Model_Matrix() { return this->model; }
	virtual glm::mat4 Get_View_Matrix() { return EngineCamera->GetViewMatrix(); }
	virtual glm::mat4 Get_Projection_Matrix() { return this->projection; }

	glm::vec3 GetForwardVector()
	{
		glm::vec3 forward = glm::vec3(1.0f);
		forward.x = cos(glm::radians(this->WorldRotation.y) * cos(glm::radians(this->WorldRotation.x)));
		forward.y = sin(glm::radians(this->WorldRotation.x));
		forward.z = sin(glm::radians(this->WorldRotation.y) * cos(glm::radians(this->WorldRotation.x)));
		return glm::vec3(normalize(forward));
	}

	glm::vec3 GetRightVector()
	{
		return glm::normalize(glm::cross(this->GetForwardVector(), this->WorldUp));
	}

	glm::vec3 GetUpVector()
	{
		return glm::normalize(glm::cross(this->GetRightVector(), this->GetForwardVector()));
	}
};