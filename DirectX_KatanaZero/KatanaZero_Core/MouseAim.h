#pragma once
#include <EngineCore/StateManager.h>

// ���� : ���콺 Ŀ�� ��� Ŭ����
class AMouseAim : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AMouseAim();
	~AMouseAim();
	
	// delete Function
	AMouseAim(const AMouseAim& _Other) = delete;
	AMouseAim(AMouseAim&& _Other) noexcept = delete;
	AMouseAim& operator=(const AMouseAim& _Other) = delete;
	AMouseAim& operator=(AMouseAim&& _Other) noexcept = delete;

	static FVector GetMouseAimLocation()
	{
		return Location;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Aim = nullptr;

private:
	void StateInit();

	static FVector Location;
	UStateManager State;
};

