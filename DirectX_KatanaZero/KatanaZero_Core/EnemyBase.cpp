#include "PreCompile.h"
#include "EnemyBase.h"

#include "PlayLevelBase.h"

const int AEnemyBase::BloodSize = 20;

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
		BloodEffect NewBloodEffect = BloodEffect();
		NewBloodEffect.Renderer = NewRenderer;
		Blood.push_back(NewBloodEffect);
	}

	SetRoot(Root);

	// 수정(삭제 필요)
	RendererFT = CreateDefaultSubObject<USpriteRenderer>("RendererFT");
	RendererFB = CreateDefaultSubObject<USpriteRenderer>("RendererFB");
	RendererBT = CreateDefaultSubObject<USpriteRenderer>("RendererBT");
	RendererBB = CreateDefaultSubObject<USpriteRenderer>("RendererBB");

	RendererFT->SetupAttachment(Root);
	RendererFB->SetupAttachment(Root);
	RendererBT->SetupAttachment(Root);
	RendererBB->SetupAttachment(Root);
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
	EffectInit();
	CollisionInit();
	DebugingRendererInit();
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
}

void AEnemyBase::DebugingRendererInit()
{
	RendererFT->SetSprite("RedPoint.png");
	RendererFB->SetSprite("RedPoint.png");
	RendererBT->SetSprite("RedPoint.png");
	RendererBB->SetSprite("RedPoint.png");

	RendererFT->SetOrder(ERenderOrder::UI);
	RendererFB->SetOrder(ERenderOrder::UI);
	RendererBT->SetOrder(ERenderOrder::UI);
	RendererBB->SetOrder(ERenderOrder::UI);

	RendererFT->SetAutoSize(4.0f, true);
	RendererFB->SetAutoSize(4.0f, true);
	RendererBT->SetAutoSize(4.0f, true);
	RendererBB->SetAutoSize(4.0f, true);
}

void AEnemyBase::DebugingUpdate()
{
	CalFourPoint(Body->GetDir());

	RendererFT->SetPosition(GetFTFromActor());
	RendererFB->SetPosition(GetFBFromActor());
	RendererBT->SetPosition(GetBTFromActor());
	RendererBB->SetPosition(GetBBFromActor());
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

void AEnemyBase::HitByPlayer(FVector _AttDir)
{
	HitDir = _AttDir;
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

void AEnemyBase::RendererDirChange()
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

void AEnemyBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	DebugingUpdate();
}

void AEnemyBase::PatrolWalkStart()
{
	TimeCount = PatrolWalkTime;
}

void AEnemyBase::PatrolWalk(float _DeltaTime)
{
	Recording(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// State Change Check
	if (0.0f > TimeCount)
	{
		State.ChangeState(EnemyState::patrol_turn);
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
	Recording(_DeltaTime);

	// State Change Check
	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState(EnemyState::patrol_stop);
		return;
	}
}

void AEnemyBase::PatrolStopStart()
{
	SetVelocityByDir(FVector::Zero);
	TimeCount = PatrolStopTime;
}

void AEnemyBase::PatrolStop(float _DeltaTime)
{
	Recording(_DeltaTime);

	// State Change Check
	if (0.0f > TimeCount)
	{
		State.ChangeState(EnemyState::patrol_walk);
		return;
	}

	TimeCount -= _DeltaTime;
}

void AEnemyBase::Run(float _DeltaTime)
{
	Recording(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);
}

void AEnemyBase::TurnStart()
{
	SetVelocityByDir({ 0.0f, 0.0f, 0.0f });
}

void AEnemyBase::Turn(float _DeltaTime)
{
	Recording(_DeltaTime);

	if (Body->IsCurAnimationEnd())
	{
		State.ChangeState(EnemyState::idle); 
		return;
	}
}

void AEnemyBase::HitFallStart()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	PlayLevel->EnemyDeadUpdate();

	if (0.0f > HitDir.X)
	{
		Body->SetDir(EEngineDir::Left);
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
	}

	SetVelocity(HitDir * 1000.0f);
	BodyCol->SetActive(false);

	DeadCol->SetPosition(BodyCol->GetLocalPosition());
	DeadCol->SetScale(BodyCol->GetLocalScale());
	DeadCol->SetActive(true);
}

void AEnemyBase::HitFall(float _DeltaTime)
{
	Recording(_DeltaTime);

	EEngineDir Dir = Body->GetDir();

	// 충돌 체크
	DeadCol->CollisionEnter(EColOrder::Door, [=](std::shared_ptr<UCollision> _Other) {	Velocity.X *= -1.0f; });

	// 속도 업데이트
	ApplyGravity(_DeltaTime);

	if (true == IsColHeadToCeil(Dir))
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -10.0f, 0.0f });
	}

	if (true == IsColWall(Dir) || true == IsColHeadToWall(Dir))
	{
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// Effect
	CreateBloodEffect(_DeltaTime);
	BloodEffectUpdate(_DeltaTime);

	// State Change Check
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir)
	||  true == IsOnGP_Boundary(Dir) || true == IsOnStairs(Dir))
	{
		State.ChangeState(EnemyState::dead);
		return;
	}
}

// State 초기화
void AEnemyBase::StateInit()
{
	// State 생성
	State.CreateState(EnemyState::idle);
	State.CreateState(EnemyState::run);
	State.CreateState(EnemyState::hitfall);
	State.CreateState(EnemyState::dead);
	State.CreateState(EnemyState::patrol_walk);
	State.CreateState(EnemyState::patrol_turn);
	State.CreateState(EnemyState::patrol_stop);
	State.CreateState(EnemyState::replay);
	State.CreateState(EnemyState::restart);


	State.CreateState(EnemyState::turn);

	// State Start 함수 세팅
	State.SetStartFunction(EnemyState::idle, std::bind(&AEnemyBase::IdleStart, this));
	State.SetStartFunction(EnemyState::run, std::bind(&AEnemyBase::RunStart, this));
	State.SetStartFunction(EnemyState::hitfall, std::bind(&AEnemyBase::HitFallStart, this));
	State.SetStartFunction(EnemyState::dead, std::bind(&AEnemyBase::DeadStart, this));
	State.SetStartFunction(EnemyState::patrol_walk, std::bind(&AEnemyBase::PatrolWalkStart, this));
	State.SetStartFunction(EnemyState::patrol_turn, std::bind(&AEnemyBase::PatrolTurnStart, this));
	State.SetStartFunction(EnemyState::patrol_stop, std::bind(&AEnemyBase::PatrolStopStart, this));
	State.SetStartFunction(EnemyState::replay, [=] 
		{
			SetRecordingActive(false);
			SetReplayStart();
		}
	);

	State.SetStartFunction(EnemyState::restart, [=] { SetRewindStart(); });


	State.SetStartFunction(EnemyState::turn, std::bind(&AEnemyBase::TurnStart, this));

	// State Update 함수 세팅
	State.SetUpdateFunction(EnemyState::idle, std::bind(&AEnemyBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::run, std::bind(&AEnemyBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::hitfall, std::bind(&AEnemyBase::HitFall, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::dead, std::bind(&AEnemyBase::Dead, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::patrol_walk, std::bind(&AEnemyBase::PatrolWalk, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::patrol_turn, std::bind(&AEnemyBase::PatrolTurn, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::patrol_stop, std::bind(&AEnemyBase::PatrolStop, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::replay, [=](float _DeltaTime) { Replaying(_DeltaTime); });
	State.SetUpdateFunction(EnemyState::restart, [=](float _DeltaTime) { Replaying(_DeltaTime); });
	

	State.SetUpdateFunction(EnemyState::turn, std::bind(&AEnemyBase::Turn, this, std::placeholders::_1));

	// State End 함수 세팅
	State.SetEndFunction(EnemyState::patrol_turn, [=] { RendererDirChange(); });
	State.SetEndFunction(EnemyState::hitfall, [=] { DeadCol->SetActive(false); });


	State.SetEndFunction(EnemyState::turn, [=] { RendererDirChange(); });
}

void AEnemyBase::Dead(float _DeltaTime)
{
	BloodEffectUpdate(_DeltaTime);
	Recording(_DeltaTime);
}

/////////
// Effect
void AEnemyBase::EffectInit()
{
	for (size_t i = 0; i < Blood.size(); i++)
	{
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter1, ImgRes::effect_blood_splatter1, 0.08f, true);
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter2, ImgRes::effect_blood_splatter2, 0.08f, true);
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter1, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter2, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetOrder(ERenderOrder::EffectBack);
		Blood[i].Renderer->SetAutoSize(3.0f, true);
		Blood[i].Renderer->SetActive(false);
	}
}

void AEnemyBase::BloodVecIdxUpdate()
{
	++BloodIdx;

	if (BloodSize <= BloodIdx)
	{
		BloodIdx = 0;
	}
}

void AEnemyBase::CreateBloodEffect(float _DeltaTime)
{
	if (0.0f < BloodTimeCount)
	{
		BloodTimeCount -= _DeltaTime;
		return;
	}

	EEngineDir Dir = Body->GetDir();

	if (true == Blood[BloodIdx].Renderer->IsActive())
	{
		return;
	}

	Blood[BloodIdx].Renderer->AnimationReset();
	Blood[BloodIdx].Renderer->SetActive(true);

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);
	switch (RandomValue)
	{
	case 1:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter1);
		break;
	case 2:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter2);
		break;
	}


	//float Deg = UEngineRandom::MainRandom.RandomFloat(5.0f, 35.0f);
	//Deg *= UEngineMath::DToR;
	//FVector VelDir = { cosf(Deg), sinf(Deg), 0.0f };

	//float Speed = UEngineRandom::MainRandom.RandomFloat(100.0f, 250.0f);

	FVector ActorVector = Velocity;
	FVector VelDir = -ActorVector;
	float Deg = UContentsMath::GetAngleToX_2D(VelDir.Normalize2DReturn());
		
	Blood[BloodIdx].BloodEffect::Velocity = VelDir * 0.15f;
	Blood[BloodIdx].Renderer->SetPosition(GetActorLocation() + FVector(0.0f, 50.0f, 0.0f));
	//Blood[BloodIdx].Renderer->AddPosition(VelDir * 50.0f);
	Blood[BloodIdx].Renderer->SetRotationDeg({ 0.0f, 0.0f, Deg });


	BloodVecIdxUpdate();

	BloodTimeCount = Const::effect_blood_splatter_delay;
}

void AEnemyBase::BloodEffectUpdate(float _DeltaTime)
{
	for (size_t i = 0; i < Blood.size(); i++)
	{
		if (false == Blood[i].Renderer->IsActive())
		{
			continue;
		}

		Blood[i].Renderer->AddPosition(Blood[i].Velocity * _DeltaTime);
	}
}