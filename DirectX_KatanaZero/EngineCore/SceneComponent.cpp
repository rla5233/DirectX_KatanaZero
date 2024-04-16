#include "PreCompile.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent() 
{
}

USceneComponent::~USceneComponent() 
{
}

void USceneComponent::SetupAttachment(USceneComponent* _Parent)
{
	SetParent(_Parent);
}