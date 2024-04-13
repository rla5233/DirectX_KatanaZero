#include "PreCompile.h"
#include "PlayerBase.h"

#include "ColMapObject.h"
#include "MouseAim.h"

APlayerBase::APlayerBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");
	Center   = CreateDefaultSubObject<USpriteRenderer>("Center");
	
	Renderer->SetupAttachment(Root);
	Center->SetupAttachment(Root);

	Renderer->SetPivot(EPivot::BOT);
	
	SetRoot(Root);
	
	InputOn();
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

	Center->SetSprite("RedPoint.png");
	Center->SetOrder(ERenderOrder::Player2);
	Center->SetAutoSize(5.0f, true);
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

bool APlayerBase::IsOnGround()
{
	bool Result = false;

	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector CurPos = GetActorLocation();
	CurPos.Y = MapTexScale.Y - CurPos.Y - 1.0f;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::YELLOW == PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsOnPlatForm()
{
	bool Result = false;

	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector CurPos = GetActorLocation();
	CurPos.Y = MapTexScale.Y - CurPos.Y - 1.0f;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::GREEN == PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsOnStairs()
{
	bool Result = false;

	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector CurPos = GetActorLocation();
	CurPos.Y = MapTexScale.Y - CurPos.Y - 1.0f;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::BLUE == PixelColor)
	{
		Result = true;
	}

	return Result;
}

void APlayerBase::OnGroundPosAdjust()
{
	while (true == IsOnGround())
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnGround())
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}
}

void APlayerBase::OnStairPosAdjust()
{
	while (true == IsOnStairs())
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnStairs())
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}	
}

void APlayerBase::RollFallPosAdjust()
{
	if (true == IsOnPlatForm() && true == IsFallInputPress())
	{
		while (true)
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			if (true == IsOnGround() || true == IsOnStairs())
			{
				AddActorLocation({ 0.0f, 1.0f, 0.0f });
				break;
			}
		}
	}
}

////////////////////
// FSM Setting Start
void APlayerBase::SetRunVel()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X = FVector::Left.X * Const::player_max_speedx;
		break;
	case EEngineDir::Right:
		Velocity.X = FVector::Right.X * Const::player_max_speedx;
		break;
	}
}

void APlayerBase::SetAttackDir()
{
	FVector AimPos = AMouseAim::GetMouseAimLocation();
	FVector CurPos = GetActorLocation();
	AttackDir = AimPos - CurPos;

	if (0.0f > AttackDir.X)
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
	}

	AttackDir.Normalize2D();
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
	EEngineDir Dir = Renderer->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += -Const::player_run_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_run_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx < std::abs(Velocity.X))
	{
		SetRunVel();
	}
}

void APlayerBase::RunGravityUpdate(float _DeltaTime)
{
	if (true == IsOnGround() || true == IsOnPlatForm() || true == IsOnStairs())
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::run_gravity * _DeltaTime;
}

void APlayerBase::GravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::gravity * _DeltaTime;

	if (-Const::player_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_max_speedy;
	}
}

void APlayerBase::FallVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += (-1.0f) * Const::player_fall_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_fall_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx < abs(Velocity.X))
	{
		JumpVelXUpdate(_DeltaTime);
	}
}

void APlayerBase::FallGravityUpdate(float _DeltaTime)
{
	if (true == IsOnGround() || true == IsOnPlatForm())
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::gravity * _DeltaTime;

	if (Const::player_fall_max_speedy < abs(Velocity.Y))
	{
		Velocity.Y = -Const::player_fall_max_speedy;
	}
}

void APlayerBase::JumpVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X = -Const::player_max_speedx;
		break;
	case EEngineDir::Right:
		Velocity.X = Const::player_max_speedx;
		break;
	}
}

void APlayerBase::JumpVelYUpdate(float _DeltaTime)
{
	Velocity.Y += Const::jump_gravity * _DeltaTime;

	if (-Const::player_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_max_speedy;
	}
}

void APlayerBase::RollVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity += FVector::Left * Const::player_roll_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity += FVector::Right * Const::player_roll_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx > abs(Velocity.X))
	{
		float Sign = Velocity.X / abs(Velocity.X);
		Velocity.X = Sign * Const::player_max_speedx;
	}
}

void APlayerBase::RollVelYUpdate()
{
	if (true == IsOnGround() || true == IsOnStairs())
	{
		Velocity.Y = 0.0f;
	}
}
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);


	// ¼öÁ¤
	if (UEngineInput::IsDown('F'))
	{
		bool IsActiveValue = Renderer->IsActive();
		IsActiveValue = !IsActiveValue;
		Renderer->SetActive(IsActiveValue);
	}
}