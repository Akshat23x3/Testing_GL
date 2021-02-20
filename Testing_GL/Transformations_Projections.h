#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CameraComponent.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

CameraComponent* EngineCamera = new CameraComponent();

class Transformations
{
	glm::vec3 Position = glm::vec3(1);
	glm::vec3 Rotation = glm::vec3(1);
	glm::vec3 Scale = glm::vec3(1);

	glm::mat4 projection = glm::perspective(EngineCamera->GetCameraZoom(), (GLfloat)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1000.0f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

protected:
	void reset_matrices()
	{
		this->Position = glm::vec3(1.0f); this->Scale = glm::vec3(1.0f); this->Rotation = glm::vec3(1.0f);
	}

public:
	glm::mat4 Project_On_Screen()
	{
		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);

		model = glm::translate(model, this->Position);
		model = glm::rotate(model, glm::radians(this->Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, Scale);

		view = EngineCamera->GetViewMatrix();

		return projection * view * model;
	}

	virtual void Set_Position(glm::vec3 Position) { this->Position = Position; }
	virtual void Set_Rotation(glm::vec3 Rotation) { this->Rotation = Rotation; }
	virtual void Set_Scale(glm::vec3 Scale) { this->Scale = Scale; }

	virtual glm::vec3 Get_Position() { return this->Position; }
	virtual glm::vec3 Get_Rotation() { return this->Rotation; }
	virtual glm::vec3 Get_Scale() { return this->Scale; }
};