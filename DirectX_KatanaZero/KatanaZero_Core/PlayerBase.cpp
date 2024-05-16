#include "PreCompile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"
#include "HeadHunterBase.h"
#include "EnemyBase.h"
#include "MouseAim.h"
#include "Door.h"

const int APlayerBase::CloudSize = 20;

APlayerBase::APlayerBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");

	AttackCol	= CreateDefaultSubObject<UCollision>("Player_Attack");
	BodyCol		= CreateDefaultSubObject<UCollision>("Player_Body");
	FrontCol	= CreateDefaultSubObject<UCollision>("Player_Front");

	AttackEffect = CreateDefaultSubObject<USpriteRenderer>("Player_Effect");
	JumpLandEffect = CreateDefaultSubObject<USpriteRenderer>("Player_Effect");
	Cloud.reserve(CloudSize);
	for (int i = 0; i < CloudSize; i++)
	{
		USpriteRenderer* NewRenderer = CreateDefaultSubObject<USpriteRenderer>("Cloud");
		CloudEffect NewCloudEffect = CloudEffect();
		NewCloudEffect.Renderer = NewRenderer;
		Cloud.push_back(NewCloudEffect);
	}

	Body->SetupAttachment(Root);
	AttackCol->SetupAttachment(Root);
	BodyCol->SetupAttachment(Root);
	FrontCol->SetupAttachment(Root);
	AttackEffect->SetupAttachment(Root);
	
	SetRoot(Root);
}

APlayerBase::~APlayerBase()
{
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	UPixelColObject::SetActor(this);
	URecordingObject::SetActor(this);
	UPhysicsObject::SetActor(this);
	UAfterImageObject::SetTargetRenderer(Body);

	RendererInit();
	CollisionInit();
	EffectInit();
	StateInit();
	SubStateInit();

	SetRecordingSize();
}

void APlayerBase::RendererInit()
{
	Body->SetOrder(ERenderOrder::Player);
	Body->SetAutoSize(2.0f, true);
	Body->SetDir(EEngineDir::Right);
	Body->SetPivot(EPivot::BOT);
}

void APlayerBase::CollisionInit()
{
	AttackCol->SetCollisionGroup(EColOrder::PlayerAttack);
	AttackCol->SetCollisionType(ECollisionType::RotRect);
	AttackCol->SetScale({ 100.0f, 75.0f, 1.0f });
	AttackCol->SetActive(false);

	BodyCol->SetCollisionGroup(EColOrder::PlayerBody);
	BodyCol->SetCollisionType(ECollisionType::Rect);

	FrontCol->SetCollisionGroup(EColOrder::PlayerFront);
	FrontCol->SetCollisionType(ECollisionType::Rect);
}

void APlayerBase::AttackCollisionCheck()
{
	AttackCol->CollisionEnter(EColOrder::Door, [=](std::shared_ptr<UCollision> _Other)
		{
			ADoor* Door = dynamic_cast<ADoor*>(_Other->GetActor());
			Door->StateChange(DoorState::open);
			AttackCol->SetActive(false);
		}
	);

	AttackCol->CollisionEnter(EColOrder::Enemy, [=](std::shared_ptr<UCollision> _Other)
		{
			AEnemyBase* Enemy = dynamic_cast<AEnemyBase*>(_Other->GetActor());
			Enemy->HitByPlayer(AttackDir);
		}
	);

	AttackCol->CollisionEnter(EColOrder::HeadHunter, [=](std::shared_ptr<UCollision> _Other)
		{
			AHeadHunterBase* HeadHunter = dynamic_cast<AHeadHunterBase*>(_Other->GetActor());
			HeadHunter->HitByPlayer(AttackDir);
		}
	);
}

bool APlayerBase::IsDirChangeKeyDown()
{
	bool Result = false;
	EEngineDir Dir = Body->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsDown('D') || true == IsDown(VK_RIGHT)))
	{
		DirChange(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsDown('A') || true == IsDown(VK_LEFT)))
	{
		DirChange(EEngineDir::Left);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsDirChangeKeyPress()
{
	bool Result = false;
	EEngineDir Dir = Body->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		DirChange(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		DirChange(EEngineDir::Left);
		Result = true;
	}

	if ((true == IsPress('D') || true == IsPress(VK_RIGHT))
	&&  (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Result = false;
	}

	return Result;
}

void APlayerBase::DirChange(EEngineDir _Dir)
{
	FVector BodyColScale = BodyCol->GetLocalScale();
	FVector FrontColScale = FrontCol->GetLocalScale();
	FVector FrontColPos = FrontCol->GetLocalPosition();

	switch (_Dir)
	{
	case EEngineDir::Left:
		Body->SetDir(EEngineDir::Left);
		FrontCol->SetPosition({ -BodyColScale.hX() - FrontColScale.hX(), FrontColPos.Y, 0.0f});
		break;
	case EEngineDir::Right:
		Body->SetDir(EEngineDir::Right);
		FrontCol->SetPosition({ BodyColScale.hX() + FrontColScale.hX(), FrontColPos.Y, 0.0f});
		break;
	}
}

////////////////////
// FSM Setting Start
void APlayerBase::SetMaxRunVel()
{
	EEngineDir Dir = Body->GetDir();

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
		DirChange(EEngineDir::Left);
	}
	else
	{
		DirChange(EEngineDir::Right);
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
	EEngineDir Dir = Body->GetDir();
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir) || true == IsOnStairs(Dir) 
	||  true == IsOnGP_Boundary(Dir) || true == IsOnCliff(Dir) || true == IsOnGroundBoundary(Dir))
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::down_stair_gravity * _DeltaTime;
}

void APlayerBase::RollDownStairGravityUpdate(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();
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
	Velocity.Y += 0.5f * Const::default_gravity * _DeltaTime;

	if ((-0.5f) * Const::player_fall_max_speedy > Velocity.Y)
	{
		Velocity.Y = (-0.5f) * Const::player_fall_max_speedy;
	}
}

void APlayerBase::JumpVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();

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
	EEngineDir Dir = Body->GetDir();

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
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += -Const::player_run_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_run_accx * _DeltaTime;
		break;
	}

	// max speedx 
	if (Const::player_max_speedx < std::abs(Velocity.X))
	{
		SetMaxRunVel();
	}
}

void APlayerBase::RunToIdleVelUpdate(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();
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

void APlayerBase::ColCheckUpdate()
{
	EEngineDir Dir = Body->GetDir();

	// OnGround
	if (true == IsOnGround(Dir))
	{
		OnGroundPosAdjust(Dir);
	}

	// OnStairs
	if (true == IsOnStairs(Dir))
	{
		if (true == IsStairsUp())
		{
			UpStairPosAdjust(Dir);
		}
	}
	
	// OnCliff
	if (true == IsOnCliff(Dir))
	{
		OnCliffPosAdjust(Dir);
	}
}
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	SubState.Update(_DeltaTime);
	
	// Debug Rendering
	DebugUpdate();
}

void APlayerBase::DebugUpdate()
{
	{
		std::string Msg = std::format("Player_Pos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player_Invincible : {}\n", IsInvincibleValue);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player_State : {}\n", GetCurMainState());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}