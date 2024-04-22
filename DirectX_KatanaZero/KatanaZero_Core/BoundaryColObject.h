#pragma once

// 설명 : 맵 경계 충돌체
class ABoundaryColObject : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABoundaryColObject();
	~ABoundaryColObject();

	// delete Function
	ABoundaryColObject(const ABoundaryColObject& _Other) = delete;
	ABoundaryColObject(ABoundaryColObject&& _Other) noexcept = delete;
	ABoundaryColObject& operator=(const ABoundaryColObject& _Other) = delete;
	ABoundaryColObject& operator=(ABoundaryColObject&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Body = nullptr;

};

