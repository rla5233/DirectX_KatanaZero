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
	if (nullptr != ChaseMark)
	{
		ChaseMark->Destroy();
		ChaseMark = nullptr;
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
	DeadCol->SetActive(false);
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

void AEnemyBase::PlayerCheck()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();

	// 좌우 체크
	FVector DiffDir = PlayerPos - GetActorLocation();

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		if (0.0f < DiffDir.X)
		{

		}
		break;
	case EEngineDir::Right:
		
		break;
	}

}

bool AEnemyBase::AttackRangeCheck()
{
	return false;
}

void AEnemyBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	
	DebugingUpdate();



	// Test
	if (UEngineInput::IsDown(VK_SPACE))
	{
		State.ChangeState(EnemyState::chase_run);
	}
}