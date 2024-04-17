#include "PreCompile.h"
#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Enemy_Renderer");
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetOrder(ERenderOrder::Enemy);
	Renderer->SetAutoSize(2.0f, true);
	Renderer->SetDir(EEngineDir::Right);
	SetRoot(Renderer);
}

AEnemyBase::~AEnemyBase()
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
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

void AEnemyBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AEnemyBase::Walk(float _DeltaTime)
{
	// ��ġ ������Ʈ
	PosUpdate(this, _DeltaTime);
}

void AEnemyBase::Run(float _DeltaTime)
{
	// ��ġ ������Ʈ
	PosUpdate(this, _DeltaTime);
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

// State �ʱ�ȭ
void AEnemyBase::StateInit()
{
	// State ����
	State.CreateState("Idle");
	State.CreateState("Walk");
	State.CreateState("Run");
	State.CreateState("Turn");

	// State Start �Լ� ����
	State.SetStartFunction("Idle", std::bind(&AEnemyBase::IdleStart, this));
	State.SetStartFunction("Walk", std::bind(&AEnemyBase::WalkStart, this));
	State.SetStartFunction("Run", std::bind(&AEnemyBase::RunStart, this));
	State.SetStartFunction("Turn", std::bind(&AEnemyBase::TurnStart, this));

	// State Update �Լ� ����
	State.SetUpdateFunction("Idle", std::bind(&AEnemyBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Walk", std::bind(&AEnemyBase::Walk, this, std::placeholders::_1));
	State.SetUpdateFunction("Run", std::bind(&AEnemyBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction("Turn", std::bind(&AEnemyBase::Turn, this, std::placeholders::_1));

	// State End �Լ� ����
	State.SetEndFunction("Turn", [=] 
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
	);
}
