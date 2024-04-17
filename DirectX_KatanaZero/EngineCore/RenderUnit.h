#pragma once
#include "EngineMesh.h"
#include "EngineMaterial.h"
#include "Camera.h"
#include "EngineShaderResources.h"

// 설명 :
class URenderUnit
{
public:
	// constrcuter destructer
	URenderUnit();
	~URenderUnit();

	std::shared_ptr<UEngineMesh> GetMesh()
	{
		return Mesh;
	}

	std::shared_ptr<UEngineMaterial> GetMaterial()
	{
		return Material;
	}

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	virtual void MaterialSettingEnd() {}

	// 기하구조를 담당하지 않아.
	// void RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera);

	std::shared_ptr<UEngineShaderResources> Resources;

	void RenderingSetting();
	void ResCopy(UEngineShader* _Shader);
	virtual void Render(float _DeltaTime);

protected:
	std::shared_ptr<UEngineInputLayOut> LayOut;
	std::shared_ptr<UEngineMesh> Mesh;
	std::shared_ptr<UEngineMaterial> Material;

};

