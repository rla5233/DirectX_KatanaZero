#pragma once
#include "SceneComponent.h"
#include "EngineMesh.h"
#include "EngineMaterial.h"

// ���� : public std::enable_shared_from_this<URenderer>
// shared_ptr�� this�� �����Ҽ� �ִ� ����� ���� Ŭ�����Դϴ�.

// URenderer�� ���� ������ �Ҽ� �ִ� ��Ȳ�̴�.
// ��緣������ ���Ҽ� �ִ�.
// �׷��� �ȵȴ�.
// ����� ������� �ʾҰ� Ưȭ����� ������� ����.
// Ưȭ���?

class UEngineShaderResources;
class URenderer : public USceneComponent, public std::enable_shared_from_this<URenderer>
{
	friend ULevel;
	GENERATED_BODY(USceneComponent)

public:

	// constrcuter destructer
	URenderer();
	~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	std::shared_ptr<UEngineShaderResources> Resources;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ResCopy(UEngineShader* _Shader);

private:
	void RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera);

	void Render(float _DeltaTime);

	std::shared_ptr<UEngineInputLayOut> LayOut;
	std::shared_ptr<UEngineMesh> Mesh;
	std::shared_ptr<UEngineMaterial> Material;
};

