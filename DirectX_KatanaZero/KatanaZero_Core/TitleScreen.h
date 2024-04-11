#pragma once
#include "ContentsEnum.h"
#include "LerpObject.h"

// ���� : Title ȭ��
class ATitleScreen : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ATitleScreen();
	~ATitleScreen();

	// delete Function
	ATitleScreen(const ATitleScreen& _Other) = delete;
	ATitleScreen(ATitleScreen&& _Other) noexcept = delete;
	ATitleScreen& operator=(const ATitleScreen& _Other) = delete;
	ATitleScreen& operator=(ATitleScreen&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* Fence = nullptr;
	USpriteRenderer* Plants = nullptr;
};

