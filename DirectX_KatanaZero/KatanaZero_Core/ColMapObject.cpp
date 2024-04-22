#include "PreCompile.h"
#include "ColMapObject.h"

AColMapObject::AColMapObject()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	ColMap = CreateDefaultSubObject<USpriteRenderer>("ColMap");
	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");

	ColMap->SetupAttachment(Root);
	BackGround->SetupAttachment(Root);

	SetRoot(Root);
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