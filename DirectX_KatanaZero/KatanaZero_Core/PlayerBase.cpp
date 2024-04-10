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

////////////////////
// FSM Setting Start
void APlayerBase::SetRunAcc()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Acc = FVector::Left * 500.0f;
		break;
	case EEngineDir::Right:
		Acc = FVector::Right * 500.0f;
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

void APlayerBase::GravityUpdate(float _DeltaTime)
{
	std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();

	FVector CurPos = GetActorLocation();
	Color8Bit PixelColor = MapTex->GetColor(CurPos, Color8Bit::Black);

	if (ColMap::YELLOW != PixelColor)
	{
		float Speed = 200.0f;
		AddActorLocation(FVector::Down * Speed * _DeltaTime);
		IsGround = false;
		return;
	}

	IsGround = true;
}

void APlayerBase::JumpPosUpdate(float _DeltaTime)
{
	float Speed = 200.0f;
	AddActorLocation(FVector::Up * Speed * _DeltaTime);
	IsGround = false;
}
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}