#include "PreCompile.h"
#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Enemy_Renderer");
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetOrder(ERenderOrder::Enemy);
	Renderer->SetAutoSize(2.0f, true);
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

void AEnemyBase::DirChange()
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
}

void AEnemyBase::Walk(float _DeltaTime)
{
	PosUpdate(this, _DeltaTime);
}

// State �ʱ�ȭ
void AEnemyBase::StateInit()
{
	// State ����
	State.CreateState("Idle");
	State.CreateState("Walk");

	// State Start �Լ� ����
	State.SetStartFunction("Idle", std::bind(&AEnemyBase::IdleStart, this));
	State.SetStartFunction("Walk", std::bind(&AEnemyBase::WalkStart, this));

	// State Update �Լ� ����
	State.SetUpdateFunction("Idle", std::bind(&AEnemyBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Walk", std::bind(&AEnemyBase::Walk, this, std::placeholders::_1));

	// State End �Լ� ����
}
