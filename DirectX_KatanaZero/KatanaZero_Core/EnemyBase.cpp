#include "PreCompile.h"
#include "EnemyBase.h"

#include "PlayLevelBase.h"
#include "PlayerBase.h"
#include "UpMark.h"

const int AEnemyBase::BloodSize = 25;

AEnemyBase::AEnemyBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Enemy_Renderer");
	BodyCol = CreateDefaultSubObject<UCollision>("Enemy_Body_Col");
	DeadCol = CreateDefaultSubObject<UCollision>("Enemy_Dead_Col"); 

	Body->SetupAttachment(Root);
	BodyCol->SetupAttachment(Root);
	DeadCol->SetupAttachment(Root);

	Blood.reserve(BloodSize);
	for (int i = 0; i < BloodSize; i++)
	{
		USpriteRenderer* NewRenderer = CreateDefaultSubObject<USpriteRenderer>("Blood");
		UBloodEffect NewBloodEffect = UBloodEffect();
		NewBloodEffect.Renderer = NewRenderer;
		Blood.push_back(NewBloodEffect);
	}

	SetRoot(Root);
}

AEnemyBase::~AEnemyBase()
{
	if (nullptr != ChaseMark)
	{
		ChaseMark->Destroy();
		ChaseMark = nullptr;
	}

	if (nullptr != TargetStair)
	{
		TargetStair = nullptr;
	}
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	UPixelColObject::SetActor(this);
	UPhysicsObject::SetActor(this);
	URecordingObject::SetActor(this);

	RendererInit();
	EffectInit();
	CollisionInit();
	StateInit();

	SetRecordingSize();
}

void AEnemyBase::RendererInit()
{
	Body->SetPivot(EPivot::BOT);
	Body->SetOrder(ERenderOrder::Enemy);
	Body->SetAutoSize(2.0f, true);
	Body->SetDir(EEngineDir::Right);
}

void AEnemyBase::CollisionInit()
{
	BodyCol->SetCollisionType(ECollisionType::Rect);
	BodyCol->SetCollisionGroup(EColOrder::Enemy);

	DeadCol->SetCollisionType(ECollisionType::Rect);
	DeadCol->SetCollisionGroup(EColOrder::DeadEnemy);
	DeadCol->SetActive(false);
}

void AEnemyBase::SetBodyDir(EEngineDir _Dir)
{
	Body->SetDir(_Dir);
}

void AEnemyBase::SetVelocityByDir(const FVector& _Vel)
{
	EEngineDir Dir = Body->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		SetVelocity({ -_Vel.X, _Vel.Y, _Vel.Z });
		break;
	case EEngineDir::Right:
		SetVelocity({ _Vel.X, _Vel.Y, _Vel.Z });
		break;
	}
}

void AEnemyBase::ChaseMarkOff()
{
	ChaseMark->SetActive(false);
}

void AEnemyBase::ChaseMarkOn()
{
	ChaseMark->SetActive(true);
}

void AEnemyBase::HitByPlayer(FVector _AttDir)
{
	HitDir = _AttDir;
	USoundManager::SoundPlay_EnemyDeadSword();
	State.ChangeState(EnemyState::hitfall);
}

void AEnemyBase::HitByDoor(EEngineDir _Dir)
{
	HitDir = { -10.0f, 2.0f, 0.0f };

	switch (_Dir)
	{
	case EEngineDir::Left:
		break;
	case EEngineDir::Right:
		HitDir.X *= -1;
		break;
	}

	HitDir.Normalize2D();
	State.ChangeState(EnemyState::hitfall);
}

void AEnemyBase::DirChange()
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetDir(EEngineDir::Right);
		break;
	case EEngineDir::Right:
		Body->SetDir(EEngineDir::Left);
		break;
	}
}

void AEnemyBase::FloorNumUpdate()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FloorNum = PlayLevel->FloorCheck(GetActorLocation().Y);
}

void AEnemyBase::ColCheckUpdate()
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

	// Platform
	if (true == IsOnPlatForm(Dir))
	{
		OnPlatFormPosAdjust(Dir);
	}

	// GP_Boundary
	if (true == IsOnGP_Boundary(Dir))
	{
		OnGP_BoundaryPosAdjust(Dir);
	}
}

void AEnemyBase::AttackDelayUpdate(float _DeltaTime)
{
	if (0.0f < AttackDelayTimeCount)
	{
		AttackDelayTimeCount -= _DeltaTime;
		return;
	}
	
	CanAttack = true;
}

void AEnemyBase::DownStairGravityUpdate(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir) || true == IsOnStairs(Dir) || true == IsOnGP_Boundary(Dir))
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::down_stair_gravity * _DeltaTime;
}

bool AEnemyBase::PlayerChaseCheck()
{
	bool Result = false;
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();

	// 谅快 眉农
	FVector DiffDir = PlayerPos - GetActorLocation();

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		if (0.0f > DiffDir.X)
		{
			Result = true;
		}
		break;
	case EEngineDir::Right:
		if (0.0f < DiffDir.X)
		{
			Result = true;
		}
		break;
	}

	// Floor 眉农
	int PlayerFloorNum = PlayLevel->GetPlayerFloorNum();
	if (PlayerFloorNum != FloorNum)
	{
		Result = false;
	}

	if (true == PlayLevel->IsCloseDoor(GetActorLocation().X, PlayerPos.X, FloorNum))
	{
		Result = false;
	}

	return Result;
}

bool AEnemyBase::ChaseTurnCheck()
{
	bool Result = false;
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();

	// 谅快 眉农
	FVector DiffDir = PlayerPos - GetActorLocation();

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		if (0.0f < DiffDir.X)
		{
			Result = true;
		}
		break;
	case EEngineDir::Right:
		if (0.0f > DiffDir.X)
		{
			Result = true;
		}
		break;
	}

	return Result;
}

bool AEnemyBase::ChaseSameFloorCheck()
{
	bool Result = false;
	
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	int PlayerFloorNum = PlayLevel->GetPlayerFloorNum();

	if (PlayerFloorNum == FloorNum)
	{
		Result = true;
	}
	
	return Result;
}


void AEnemyBase::ChaseMarkUpdate()
{
	ChaseMark->SetActorLocation(GetActorLocation() + FVector(0.0f, 100.0f, 0.0f));
}

AStair* AEnemyBase::FindStair()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	int PlayerFloorNum = PlayLevel->GetPlayerFloorNum();
	AStair* Stair = nullptr;

	if (PlayerFloorNum < FloorNum)
	{
		Stair = PlayLevel->FindStair(EStairType::Down, FloorNum);
	}
	else if (PlayerFloorNum > FloorNum)
	{
		Stair = PlayLevel->FindStair(EStairType::Up, FloorNum);
	}

	return Stair;
}

bool AEnemyBase::AttackRangeCheck()
{
	return false;
}

void AEnemyBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	AttackDelayUpdate(_DeltaTime);
}