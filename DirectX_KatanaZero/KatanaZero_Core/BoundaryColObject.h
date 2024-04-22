#pragma once

// ���� : �� ��� �浹ü
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

