#include "PreCompile.h"
#include "EnemyBase.h"



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



/////////
// Effect
void AEnemyBase::EffectInit()
{
	for (size_t i = 0; i < Blood.size(); i++)
	{
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter1, ImgRes::effect_blood_splatter1, 0.06f, true);
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter2, ImgRes::effect_blood_splatter2, 0.06f, true);
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter3, ImgRes::effect_blood_splatter3, 0.06f, true);
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter1, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter2, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter3, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetOrder(ERenderOrder::EffectBack);
		Blood[i].Renderer->SetAutoSize(2.5f, true);
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

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter1);
		break;
	case 2:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter2);
		break;
	case 3:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter3);
	}

	FVector VelDir = -UPhysicsObject::Velocity.Normalize2DReturn();
	float Deg = UContentsMath::GetAngleToX_2D(VelDir);
	Deg += UEngineRandom::MainRandom.RandomFloat(-35.0f, 35.0f);
	Blood[BloodIdx].Renderer->SetRotationDeg({ 0.0f, 0.0f, Deg });

	float Rad = Deg * UEngineMath::DToR;
	VelDir = { cosf(Rad), sinf(Rad), 0.0f };
	Blood[BloodIdx].BloodEffect::Velocity = VelDir * 150.0f;
	Blood[BloodIdx].Renderer->SetPosition(GetActorLocation() + FVector(0.0f, 50.0f, 0.0f));
	Blood[BloodIdx].Renderer->AddPosition(VelDir * 40.0f);

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