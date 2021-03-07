#include "ModelLoading.h"

class MeshComponent : public Transformations
{
	Model* model = 0;
public:
	MeshComponent()
	{
	}

	void Load_Model(const GLchar* model_path)
	{
		model = new Model(model_path);
	}

	Shader_Object* GetShader() { return model->GetShader(); }

	void Draw()
	{
		model->Draw(this);
	}
};