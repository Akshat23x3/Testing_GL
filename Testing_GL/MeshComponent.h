#include "ModelLoading.h"

class MeshComponent : public Transformations
{
	Model* model = 0;
public:
	MeshComponent()
	{
	}

	Shader_Object* Load_Model(const GLchar* model_path)
	{
		model = new Model(model_path);
		return GetShader();
	}

	Shader_Object* GetShader() { return model->GetShader(); }

	void Draw()
	{
		model->Draw(this);
	}
};