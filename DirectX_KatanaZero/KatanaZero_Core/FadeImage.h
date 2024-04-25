#pragma once
#include "FadeObject.h"

// Ό³Έν :
class UFadeImage : public UImage, public UFadeObject
{
	GENERATED_BODY(UImage);
public:
	// constrcuter destructer
	UFadeImage();
	~UFadeImage();

	// delete Function
	UFadeImage(const UFadeImage& _Other) = delete;
	UFadeImage(UFadeImage&& _Other) noexcept = delete;
	UFadeImage& operator=(const UFadeImage& _Other) = delete;
	UFadeImage& operator=(UFadeImage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DelatTime) override;

private:

};

