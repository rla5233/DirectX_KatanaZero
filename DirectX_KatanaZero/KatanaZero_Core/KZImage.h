#pragma once
#include "FadeObject.h"

// Ό³Έν :
class UKZImage : public UImage, public UFadeObject
{
	GENERATED_BODY(UImage);
public:
	// constrcuter destructer
	UKZImage();
	~UKZImage();

	// delete Function
	UKZImage(const UKZImage& _Other) = delete;
	UKZImage(UKZImage&& _Other) noexcept = delete;
	UKZImage& operator=(const UKZImage& _Other) = delete;
	UKZImage& operator=(UKZImage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DelatTime) override;

private:

};

