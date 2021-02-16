#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformations
{

	glm::vec3 Position = glm::vec3(1);
	glm::vec3 Rotation = glm::vec3(1);
	glm::vec3 Scale = glm::vec3(1);

protected:
	void reset_matrices()
	{
		this->Position = glm::vec3(1.0f); this->Scale = glm::vec3(1.0f); this->Rotation = glm::vec3(1.0f);
	}

public:
	glm::mat4 Transform()
	{
		glm::mat4 transform = glm::mat4(1);
		transform = glm::translate(transform, this->Position);
		transform = glm::rotate(transform, glm::radians(this->Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(this->Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(this->Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, Scale);
		return transform;
	}

	virtual void Set_Position(glm::vec3 Position) { this->Position = Position; }
	virtual void Set_Rotation(glm::vec3 Rotation) { this->Rotation = Rotation; }
	virtual void Set_Scale(glm::vec3 Scale) { this->Scale = Scale; }

	virtual glm::vec3 Get_Position() { return this->Position; }
	virtual glm::vec3 Get_Rotation() { return this->Rotation; }
	virtual glm::vec3 Get_Scale() { return this->Scale; }
};