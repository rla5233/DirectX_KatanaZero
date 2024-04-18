#include "PreCompile.h"
#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Enemy_Renderer");
	BodyCol  = CreateDefaultSubObject<UCollision>("Enemy_Body_Col");

	Renderer->SetupAttachment(Root);
	BodyCol->SetupAttachment(Root);

	SetRoot(Root);
}

AEnemyBase::~AEnemyBase()
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	UPixelColObject::SetActor(this);
	UPhysicsObject::SetActor(this);
	URecordingObject::SetActor(this);

	RendererInit();
	CollisionInit();
	StateInit();
}

void AEnemyBase::RendererInit()
{
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetOrder(ERenderOrder::Enemy);
	Renderer->SetAutoSize(2.0f, true);
	Renderer->SetDir(EEngineDir::Right);
}

void AEnemyBase::CollisionInit()
{
	BodyCol->SetScale({ 100.0f, 100.0f, 100.0f });
	BodyCol->SetCollisionGroup(EColOrder::Enemy);
	BodyCol->SetCollisionType(ECollisionType::RotRect);
}

void AEnemyBase::SetVelocityByDir(const FVector& _Vel)
{
	EEngineDir Dir = Renderer->GetDir();

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

void AEnemyBase::RendererDirChange()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Renderer->SetDir(EEngineDir::Right);
		break;
	case EEngineDir::Right:
		Renderer->SetDir(EEngineDir::Left);
		break;
	}
}

void AEnemyBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	DefaultUpdate(_DeltaTime);
}

void AEnemyBase::DefaultUpdate(float _DeltaTime)
{
	std::string CurState = State.GetCurStateName();

	if ("Replay" != CurState)
	{
		Recording(_DeltaTime);
	}
}

void AEnemyBase::PatrolWalk(float _DeltaTime)
{
	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// State Change Check
	if (0.0f > TimeCount)
	{
		State.ChangeState("PatrolTurn");
		return;
	}

	TimeCount -= _DeltaTime;
}

void AEnemyBase::PatrolTurnStart()
{
	SetVelocityByDir(FVector::Zero);
}

void AEnemyBase::PatrolTurn(float _DeltaTime)
{
	// State Change Check
	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("PatrolStop");
		return;
	}
}

void AEnemyBase::PatrolStopStart()
{
	SetVelocityByDir(FVector::Zero);
}

void AEnemyBase::PatrolStop(float _DeltaTime)
{
	// State Change Check
	if (0.0f > TimeCount)
	{
		State.ChangeState("PatrolWalk");
		return;
	}

	TimeCount -= _DeltaTime;
}

void AEnemyBase::Run(float _DeltaTime)
{
	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);
}

void AEnemyBase::TurnStart()
{
	SetVelocityByDir({ 0.0f, 0.0f, 0.0f });
}

void AEnemyBase::Turn(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle"); 
		return;
	}
}

void AEnemyBase::HitFall(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	// �ӵ� ������Ʈ
	ApplyGravity(_DeltaTime);

	if (true == IsColHeadToCeil(Dir))
	{
		Velocity.Y = 0.0f;
	}

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// State Change Check
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir)
	||  true == IsOnGP_Boundary(Dir) || true == IsOnStairs(Dir))
	{
		State.ChangeState("Dead");
		return;
	}
}

void AEnemyBase::ReplayStart()
{
	SetReplayStart();
}

void AEnemyBase::Replay(float _DeltaTime)
{
	Replaying(_DeltaTime);
}

// State �ʱ�ȭ
void AEnemyBase::StateInit()
{
	// State ����
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("HitFall");
	State.CreateState("Dead");
	State.CreateState("PatrolWalk");
	State.CreateState("PatrolTurn");
	State.CreateState("PatrolStop");
	State.CreateState("Replay");


	State.CreateState("Turn");

	// State Start �Լ� ����
	State.SetStartFunction("Idle", std::bind(&AEnemyBase::IdleStart, this));
	State.SetStartFunction("Run", std::bind(&AEnemyBase::RunStart, this));
	State.SetStartFunction("HitFall", std::bind(&AEnemyBase::HitFallStart, this));
	State.SetStartFunction("Dead", std::bind(&AEnemyBase::DeadStart, this));
	State.SetStartFunction("PatrolWalk", std::bind(&AEnemyBase::PatrolWalkStart, this));
	State.SetStartFunction("PatrolTurn", std::bind(&AEnemyBase::PatrolTurnStart, this));
	State.SetStartFunction("PatrolStop", std::bind(&AEnemyBase::PatrolStopStart, this));
	State.SetStartFunction("Replay", std::bind(&AEnemyBase::ReplayStart, this));
	


	State.SetStartFunction("Turn", std::bind(&AEnemyBase::TurnStart, this));

	// State Update �Լ� ����
	State.SetUpdateFunction("Idle", std::bind(&AEnemyBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Run", std::bind(&AEnemyBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction("HitFall", std::bind(&AEnemyBase::HitFall, this, std::placeholders::_1));
	State.SetUpdateFunction("Dead", std::bind(&AEnemyBase::Dead, this, std::placeholders::_1));
	State.SetUpdateFunction("PatrolWalk", std::bind(&AEnemyBase::PatrolWalk, this, std::placeholders::_1));
	State.SetUpdateFunction("PatrolTurn", std::bind(&AEnemyBase::PatrolTurn, this, std::placeholders::_1));
	State.SetUpdateFunction("PatrolStop", std::bind(&AEnemyBase::PatrolStop, this, std::placeholders::_1));
	State.SetUpdateFunction("Replay", std::bind(&AEnemyBase::Replay, this, std::placeholders::_1));
	

	State.SetUpdateFunction("Turn", std::bind(&AEnemyBase::Turn, this, std::placeholders::_1));

	// State End �Լ� ����
	State.SetEndFunction("PatrolTurn", [=] { RendererDirChange(); });



	State.SetEndFunction("Turn", [=] {	RendererDirChange(); });
}
