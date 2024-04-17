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

// State 초기화
void AEnemyBase::StateInit()
{
	// State 생성
	State.CreateState("Idle");
	State.CreateState("Walk");

	// State Start 함수 세팅
	State.SetStartFunction("Idle", std::bind(&AEnemyBase::IdleStart, this));
	State.SetStartFunction("Walk", std::bind(&AEnemyBase::WalkStart, this));

	// State Update 함수 세팅
	State.SetUpdateFunction("Idle", std::bind(&AEnemyBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Walk", std::bind(&AEnemyBase::Walk, this, std::placeholders::_1));

	// State End 함수 세팅
}
