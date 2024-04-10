#include "PreCompile.h"
#include "ColMapObject.h"

std::shared_ptr<UEngineTexture> AColMapObject::MapTex = nullptr;

AColMapObject::AColMapObject()
{
	ColMap = CreateDefaultSubObject<USpriteRenderer>("ColMap");
	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
}

AColMapObject::~AColMapObject()
{
}

void AColMapObject::BeginPlay()
{
	Super::BeginPlay();

	ColMap->SetOrder(ERenderOrder::ColMap);
	BackGround->SetOrder(ERenderOrder::BackGround);
}

void AColMapObject::ActiveSwitchCheck()
{
	if (UEngineInput::IsDown('M'))
	{
		bool IsActiveValue = BackGround->IsActive();
		IsActiveValue = !IsActiveValue;
		BackGround->SetActive(IsActiveValue);
	}
}

void AColMapObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ActiveSwitchCheck();
}