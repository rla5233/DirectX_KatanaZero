#include "PreCompile.h"
#include "KZImage.h"

UKZImage::UKZImage()
{
	UFadeObject::SetImage(this);
}

UKZImage::~UKZImage()
{
}

void UKZImage::BeginPlay()
{
	Super::BeginPlay();	
}

void UKZImage::Tick(float _DelatTime)
{
	Super::Tick(_DelatTime);

	FadeUpdate(_DelatTime);
}