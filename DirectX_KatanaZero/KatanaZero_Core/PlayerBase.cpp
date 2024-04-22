#include "PreCompile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"
#include "MouseAim.h"
#include "EnemyBase.h"
#include "Door.h"

APlayerBase::APlayerBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");
	Front_Top	= CreateDefaultSubObject<USpriteRenderer>("Front_Top");
	Front_Bot	= CreateDefaultSubObject<USpriteRenderer>("Front_Bot");
	Back_Top	= CreateDefaultSubObject<USpriteRenderer>("Back_Top");
	Back_Bot	= CreateDefaultSubObject<USpriteRenderer>("Back_Bot");

	AttackCol	= CreateDefaultSubObject<UCollision>("Player_Attack");
	BodyCol		= CreateDefaultSubObject<UCollision>("Player_Body");
	FrontCol = CreateDefaultSubObject<UCollision>("Player_Front");

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
	Back_Top->SetupAttachment(Root);
	Back_Bot->SetupAttachment(Root);
	Front_Top->SetupAttachment(Root);
	Front_Bot->SetupAttachment(Root);
	AttackCol->SetupAttachment(Root);
	BodyCol->SetupAttachment(Root);
	FrontCol->SetupAttachment(Root);
	AttackEffect->SetupAttachment(Root);
	
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
	UPhysicsObject::SetActor(this);

	RendererInit();
	CollisionInit();
	EffectInit();
	StateInit();

	SetRecordingSize();
}

void APlayerBase::RendererInit()
{
	Body->SetOrder(ERenderOrder::Player);
	Body->SetAutoSize(2.0f, true);
	Body->SetDir(EEngineDir::Right);
	Body->SetPivot(EPivot::BOT);

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
	AttackCol->SetScale({ 60.0f, 75.0f, 1.0f });
	AttackCol->SetActive(false);

	BodyCol->SetCollisionGroup(EColOrder::PlayerBody);
	BodyCol->SetCollisionType(ECollisionType::Rect);

	FrontCol->SetCollisionGroup(EColOrder::PlayerFront);
	FrontCol->SetCollisionType(ECollisionType::Rect);
}

void APlayerBase::DefaultUpdate(float _DeltaTime)
{
	AttackDelayTimeUpdate(_DeltaTime);
	SetCroudEffectUpdate(_DeltaTime);
	DoorColCheck();

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

void APlayerBase::AttackCollisionCheck()
{
	AttackCol->CollisionEnter(EColOrder::Door, [=](std::shared_ptr<UCollision> _Other)
		{
			ADoor* Door = dynamic_cast<ADoor*>(_Other->GetActor());
			Door->StateChange("Open");
			AttackCol->SetActive(false);
		}
	);

	AttackCol->CollisionEnter(EColOrder::Enemy, [=](std::shared_ptr<UCollision> _Other)
		{
			AEnemyBase* Enemy = dynamic_cast<AEnemyBase*>(_Other->GetActor());
			Enemy->HitByPlayer(AttackDir);
		}
	);
}

void APlayerBase::DoorColCheck()
{
	FrontCol->Collision(static_cast<int>(EColOrder::Door),
		[=](std::shared_ptr<UCollision> _Other)	{ IsColDoorValue = true; },
		nullptr,
		[=](std::shared_ptr<UCollision> _Other)	{ IsColDoorValue = false; }
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
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir) || true == IsOnStairs(Dir) || true == IsOnGP_Boundary(Dir))
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
	Velocity.Y += 0.75f * Const::default_gravity * _DeltaTime;

	if (-Const::player_fall_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_fall_max_speedy;
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

	// max speedx üũ
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
		OnGroundPosAdjust(Dir);
	}

	// OnStairs
	if (true == IsOnStairs(Dir))
	{
		if (true == IsStairsUp())
		{
			Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
			Back_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
			UpStairPosAdjust(Dir);
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
	
	// Debug Rendering
	DebugUpdate();
}


void APlayerBase::DebugUpdate()
{
	CalFourPoint(Body->GetDir());

	Front_Top->SetPosition(GetFTFromActor());
	Front_Bot->SetPosition(GetFBFromActor());
	Back_Top->SetPosition(GetBTFromActor());
	Back_Bot->SetPosition(GetBBFromActor());
}