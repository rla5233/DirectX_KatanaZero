#include "PreCompile.h"
#include "PlayerBase.h"

APlayerBase::APlayerBase()
{
	InputOn();

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");
}

APlayerBase::~APlayerBase()
{
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}
