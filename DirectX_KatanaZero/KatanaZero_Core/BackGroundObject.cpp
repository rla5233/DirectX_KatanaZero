#include "PreCompile.h"
#include "BackGroundObject.h"

ABackGroundObject::ABackGroundObject()
{
	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
}

ABackGroundObject::~ABackGroundObject()
{
}

void ABackGroundObject::BeginPlay()
{
	Super::BeginPlay();

	BackGround->SetOrder(ERenderOrder::BackGround);
}

void ABackGroundObject::ActiveSwitchCheck()
{
	if (UEngineInput::IsDown('M'))
	{
		bool IsActiveValue = BackGround->IsActive();
		IsActiveValue = !IsActiveValue;
		BackGround->SetActive(IsActiveValue);
	}
}

void ABackGroundObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ActiveSwitchCheck();
}