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

	if (true == IsOnGround() || true == IsOnPlatForm())
	{
		while (true)
		{
			AddActorLocation({ 0.0f, 1.0f, 0.0f });

			if (false == IsOnGround() && false == IsOnPlatForm())
			{
				AddActorLocation({ 0.0f, -1.0f, 0.0f });
				break;
			}
		}		
	}
}

void APlayerBase::RunVelUpdate(float _DeltaTime)
{
	Velocity += Acc * _DeltaTime;

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

void APlayerBase::OnGroundPosUpdate()
{
	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector CurPos = GetActorLocation();
	CurPos.Y = MapTexScale.Y - CurPos.Y;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::YELLOW == PixelColor || ColMap::GREEN == PixelColor)
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });
		return;
	}
	else
	{
		AddActorLocation({ 0.0f, -1.0f, 0.0f });
		return;
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
	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector CurPos = GetActorLocation();
	CurPos.Y = MapTexScale.Y - CurPos.Y;
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::YELLOW != PixelColor
		&& ColMap::GREEN != PixelColor)
	{
		Velocity.Y += Const::jump_gravity * _DeltaTime;

		if (-Const::player_max_speedy > Velocity.Y)
		{
			Velocity.Y = -Const::player_max_speedy;
		}

		return;
	}

	Velocity.Y = 0.0f;
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
}