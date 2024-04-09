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

	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetAutoSize(2.0f, true);
}

bool APlayerBase::IsRunInputStart()
{
	bool Result = false;

	if (true == IsDown('A') || true == IsDown(VK_LEFT))
	{
		Renderer->SetDir(EEngineDir::Left);
		Result = true;
	}

	if (true == IsDown('D') || true == IsDown(VK_RIGHT))
	{
		Renderer->SetDir(EEngineDir::Right);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsRunInputPress()
{
	bool IsRunValue = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		IsRunValue = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		IsRunValue = true;
	}

	return IsRunValue;
}

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}