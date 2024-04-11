#include "PreCompile.h"
#include "PlayerBase.h"

#include "ColMapObject.h"

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

bool APlayerBase::IsDirChangeKeyDown()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsDown('D') || true == IsDown(VK_RIGHT)))
	{
		Renderer->SetDir(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsDown('A') || true == IsDown(VK_LEFT)))
	{
		Renderer->SetDir(EEngineDir::Left);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsDirChangeKeyPress()
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

	if ((true == IsPress('D') || true == IsPress(VK_RIGHT))
	&&  (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Result = false;
	}

	return Result;
}

////////////////////
// FSM Setting Start
void APlayerBase::SetRunAcc()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Acc = FVector::Left * 5000.0f;
		break;
	case EEngineDir::Right:
		Acc = FVector::Right * 5000.0f;
		break;
	}
}

void APlayerBase::SetRunVel()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity = FVector::Left * MaxSpeed_X;
		break;
	case EEngineDir::Right:
		Velocity = FVector::Right * MaxSpeed_X;
		break;
	}
}
// FSM Setting End
//////////////////

////////////////////
// FSM Update Start
void APlayerBase::PosUpdate(float _DeltaTime)
{
	AddActorLocation(Velocity * _DeltaTime);
}

void APlayerBase::RunVelUpdate(float _DeltaTime)
{
	Velocity += Acc * _DeltaTime;

	if (MaxSpeed_X < std::abs(Velocity.X))
	{
		SetRunVel();
	}
}

void APlayerBase::GravityUpdate(float _DeltaTime)
{
	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector CurPos = GetActorLocation();
	CurPos.Y = MapTexScale.Y - CurPos.Y;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::YELLOW != PixelColor)
	{
		Velocity.Y += -2000.0f * _DeltaTime;

		if (-MaxSpeed_Y > Velocity.Y)
		{
			Velocity.Y = -MaxSpeed_Y;
		}

		IsGround = false;
		return;
	}

	Velocity.Y = 0.0f;
	IsGround = true;
}

void APlayerBase::JumpVelUpdate(float _DeltaTime)
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
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}