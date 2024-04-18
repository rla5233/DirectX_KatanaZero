#include "PreCompile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"
#include "MouseAim.h"

APlayerBase::APlayerBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Renderer	= CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");
	Front_Top	= CreateDefaultSubObject<USpriteRenderer>("Front_Top");
	Front_Bot	= CreateDefaultSubObject<USpriteRenderer>("Front_Bot");
	Back_Top	= CreateDefaultSubObject<USpriteRenderer>("Back_Top");
	Back_Bot	= CreateDefaultSubObject<USpriteRenderer>("Back_Bot");

	AttackCol	= CreateDefaultSubObject<UCollision>("Player_Attack");
	BodyCol		= CreateDefaultSubObject<UCollision>("Player_Body");

	Renderer->SetupAttachment(Root);
	Back_Top->SetupAttachment(Root);
	Back_Bot->SetupAttachment(Root);
	Front_Top->SetupAttachment(Root);
	Front_Bot->SetupAttachment(Root);
	AttackCol->SetupAttachment(Root);
	BodyCol->SetupAttachment(Root);
	
	SetRoot(Root);
	InputOn();
}

APlayerBase::~APlayerBase()
{
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	UPixelColObject::SetActor(this);
	URecordingObject::SetActor(this);

	RendererInit();
	CollisionInit();
	StateInit();

	SetRecordingSize(0.0f);
}

void APlayerBase::RendererInit()
{
	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetAutoSize(2.0f, true);
	Renderer->SetDir(EEngineDir::Right);
	Renderer->SetPivot(EPivot::BOT);

	Front_Top->SetSprite("RedPoint.png");
	Front_Top->SetOrder(ERenderOrder::Player2);
	Front_Top->SetAutoSize(4.0f, true);
	
	Front_Bot->SetSprite("RedPoint.png");
	Front_Bot->SetOrder(ERenderOrder::Player2);
	Front_Bot->SetAutoSize(4.0f, true);

	Back_Top->SetSprite("RedPoint.png");
	Back_Top->SetOrder(ERenderOrder::Player2);
	Back_Top->SetAutoSize(4.0f, true);

	Back_Bot->SetSprite("RedPoint.png");
	Back_Bot->SetOrder(ERenderOrder::Player2);
	Back_Bot->SetAutoSize(4.0f, true);
}

void APlayerBase::CollisionInit()
{
	AttackCol->SetCollisionGroup(EColOrder::PlayerAttack);
	AttackCol->SetCollisionType(ECollisionType::RotRect);
	AttackCol->SetScale({ 150.0f, 75.0f, 0.0f });
	AttackCol->SetActive(false);

	BodyCol->SetCollisionGroup(EColOrder::Player);
	BodyCol->SetCollisionType(ECollisionType::RotRect);
}

void APlayerBase::DefaultUpdate(float _DeltaTime)
{
	AttackDelayTimeUpdate(_DeltaTime);
	
	std::string CurState = State.GetCurStateName();

	if ("Replay" != CurState)
	{
		Recording(_DeltaTime);
	}
}

void APlayerBase::AttackDelayTimeUpdate(float _DeltaTime)
{
	if (0.0f >= AttackDelayTimeCount)
	{
		CanAttack = true;
		return;
	}

	AttackDelayTimeCount -= _DeltaTime;
}

bool APlayerBase::IsDirChangeKeyDown()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsDown('D') || true == IsDown(VK_RIGHT)))
	{
		RendererDirChange(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsDown('A') || true == IsDown(VK_LEFT)))
	{
		RendererDirChange(EEngineDir::Left);
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
		RendererDirChange(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		RendererDirChange(EEngineDir::Left);
		Result = true;
	}

	if ((true == IsPress('D') || true == IsPress(VK_RIGHT))
	&&  (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Result = false;
	}

	return Result;
}

void APlayerBase::RendererDirChange(EEngineDir _Dir)
{
	switch (_Dir)
	{
	case EEngineDir::Left:
		Renderer->SetDir(EEngineDir::Left);
		break;
	case EEngineDir::Right:
		Renderer->SetDir(EEngineDir::Right);
		break;
	}
}

void APlayerBase::OnGroundPosAdjust()
{
	EEngineDir Dir = Renderer->GetDir();

	while (true == IsOnGround(Dir))
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnGround(Dir))
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}
}

void APlayerBase::UpStairPosAdjust()
{
	EEngineDir Dir = Renderer->GetDir();

	while (true == IsOnStairs(Dir))
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnStairs(Dir))
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}	
}

////////////////////
// FSM Setting Start
void APlayerBase::SetMaxRunVel()
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

void APlayerBase::SetAttackDir()
{
	FVector AimPos = AMouseAim::GetMouseAimLocation();
	FVector CurPos = GetActorLocation();
	AttackDir = AimPos - CurPos;

	if (0.0f > AttackDir.X)
	{
		RendererDirChange(EEngineDir::Left);
	}
	else
	{
		RendererDirChange(EEngineDir::Right);
	}

	AttackDir.Normalize2D();
}
// FSM Setting End
//////////////////

////////////////////
// FSM Update Start
void APlayerBase::GravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::default_gravity * _DeltaTime;

	if (-Const::player_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_max_speedy;
	}
}

void APlayerBase::DownStairGravityUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir) || true == IsOnStairs(Dir) || true == IsOnGP_Boundary(Dir))
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::down_stair_gravity * _DeltaTime;
}

void APlayerBase::RollDownStairGravityUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();
	if (true == IsOnGround(Dir) || true == IsOnStairs(Dir) || true == IsOnGP_Boundary(Dir))
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += 5.0f * Const::down_stair_gravity * _DeltaTime;
}

void APlayerBase::JumpGravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::jump_gravity * _DeltaTime;

	if (-Const::player_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_max_speedy;
	}
}

void APlayerBase::FallGravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::default_gravity * _DeltaTime;

	if (-Const::player_fall_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_fall_max_speedy;
	}
}

void APlayerBase::WallGravityUpdate(float _DeltaTime)
{
	Velocity.Y += 0.75f * Const::default_gravity * _DeltaTime;

	if (-Const::player_fall_max_speedy > Velocity.Y)
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
		Velocity.X += -Const::player_jump_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_jump_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx < Velocity.X)
	{
		Velocity.X = Const::player_max_speedx;
	}

	if (-Const::player_max_speedx > Velocity.X)
	{
		Velocity.X = -Const::player_max_speedx;
	}
}

void APlayerBase::FallVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += -Const::player_fall_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_fall_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx < Velocity.X)
	{
		Velocity.X = Const::player_max_speedx;
	}

	if (-Const::player_max_speedx > Velocity.X)
	{
		Velocity.X = -Const::player_max_speedx;
	}
}

void APlayerBase::IdleToRunVelUpdate(float _DeltaTime)
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

	// max speedx üũ
	if (Const::player_max_speedx < std::abs(Velocity.X))
	{
		SetMaxRunVel();
	}
}

void APlayerBase::RunToIdleVelUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();
	float FrictionAcc = 3000.0f;

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += FrictionAcc * _DeltaTime;
		if (0.0f < Velocity.X)
		{
			Velocity.X = 0.0f;
		}
		break;
	case EEngineDir::Right:
		Velocity.X += -FrictionAcc * _DeltaTime;
		if (0.0f > Velocity.X)
		{
			Velocity.X = 0.0f;
		}
		break;
	}
}

void APlayerBase::PosUpdate(float _DeltaTime)
{
	AddActorLocation(Velocity * _DeltaTime);
}

void APlayerBase::ColCheckUpdate()
{
	EEngineDir Dir = Renderer->GetDir();

	Front_Top->SetPlusColor({ 0.0f, 0.0f, 0.0f });
	Front_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
	Back_Top->SetPlusColor({ 0.0f, 0.0f, 0.0f });
	Back_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });

	// ColWall
	if (true == IsColWall(Dir))
	{
		Front_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// OnGround
	if (true == IsOnGround(Dir))
	{
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		OnGroundPosAdjust();
	}

	// OnStairs
	if (true == IsOnStairs(Dir))
	{
		if (true == IsStairsUp())
		{
			Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
			Back_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
			UpStairPosAdjust();
		}
		else
		{
			Front_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
			Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		}
	}

	// Platform
	if (true == IsOnPlatForm(Dir))
	{
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// GP_Boundary
	if (true == IsOnGP_Boundary(Dir))
	{
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// ColHeadToWall
	if (true == IsColHeadToWall(Dir))
	{
		Front_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// ColHeadToCeil
	if (true == IsColHeadToCeil(Dir))
	{
		Front_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}
}
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	DefaultUpdate(_DeltaTime);
	DebugUpdate();
}


void APlayerBase::DebugUpdate()
{
	CalFourPoint(Renderer->GetDir());

	Front_Top->SetPosition(GetFTFromActor());
	Front_Bot->SetPosition(GetFBFromActor());
	Back_Top->SetPosition(GetBTFromActor());
	Back_Bot->SetPosition(GetBBFromActor());
}