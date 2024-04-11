#include "PreCompile.h"
#include "PlayerBase.h"

#include "ColMapObject.h"

APlayerBase::APlayerBase()
{
	InputOn();

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");
	Center   = CreateDefaultSubObject<USpriteRenderer>("Center");
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
	Center->SetAutoSize(1.0f, true);
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
	CurPos.Y = MapTexScale.Y - CurPos.Y;
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
	CurPos.Y = MapTexScale.Y - CurPos.Y;
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
	CurPos.Y = MapTexScale.Y - CurPos.Y;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::BLUE == PixelColor)
	{
		Result = true;
	}

	return Result;
}

void APlayerBase::OnStairPosAdjust()
{
	if (true == IsOnStairs())
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });
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
		Velocity = FVector::Left * Const::player_max_speedx;
		break;
	case EEngineDir::Right:
		Velocity = FVector::Right * Const::player_max_speedx;
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

void APlayerBase::GravityUpdate(float _DeltaTime)
{
	if (true == IsOnGround() || true == IsOnPlatForm())
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::gravity * _DeltaTime;

	if (Const::player_max_speedy < abs(Velocity.Y))
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
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);



	// ¼öÁ¤
	FVector Pos = GetActorLocation();
	Center->Transform.SetPosition(Pos);

	if (UEngineInput::IsDown('F'))
	{
		bool IsActiveValue = Renderer->IsActive();
		IsActiveValue = !IsActiveValue;
		Renderer->SetActive(IsActiveValue);
	}
}