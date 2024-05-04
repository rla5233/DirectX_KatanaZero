#pragma once
#include "FadeImage.h"
#include "LerpImage.h"

enum class ESortType
{
	None,
	Left
};

// Ό³Έν :
class UKZImage : public UImage, public UFadeImage, public ULerpImage
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

	void SetPosition(const FVector& _Pos) override;

	void SetSortType(ESortType _SortType);

protected:
	void BeginPlay() override;
	void Tick(float _DelatTime) override;

private:
	ESortType SortType = ESortType::None;

};

