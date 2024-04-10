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

////////////////////////
// FSM Input Check Start
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
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsRunDirChange()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();
	
	if ((EEngineDir::Left == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		Renderer->SetDir(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Renderer->SetDir(EEngineDir::Left);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsCrouchInputStart()
{
	bool Result = false;

	if (true == IsPress('S') || true == IsPress(VK_DOWN))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsCrouchInputPressEnd()
{
	bool Result = false;

	if (false == IsPress('S') && false == IsPress(VK_DOWN))
	{
		Result = true;
	}

	return Result;
}
bool APlayerBase::IsRollInputStart()
{
	bool Result = false;




	return Result;
}
// FSM Input Check End
//////////////////////

////////////////////
// FSM Setting Start
void APlayerBase::SetRunAcc()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Acc.X = -500.0f;
		break;
	case EEngineDir::Right:
		Acc.X = 500.0f;
		break;
	}
}

void APlayerBase::SetRunVel()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X = -MaxSpeed_X;
		break;
	case EEngineDir::Right:
		Velocity.X = MaxSpeed_X;
		break;
	}
}
// FSM Setting End
//////////////////

////////////////////
// FSM Update Start
void APlayerBase::RunVelUpdate(float _DeltaTime)
{
	Velocity += Acc * _DeltaTime;

	if (MaxSpeed_X < std::abs(Velocity.X))
	{
		SetRunVel();
	}
}

void APlayerBase::RunPosUpdate(float _DeltaTime)
{
	AddActorLocation(Velocity * _DeltaTime);
}
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}