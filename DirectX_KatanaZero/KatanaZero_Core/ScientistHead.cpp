#include "PreCompile.h"
#include "ScientistHead.h"

AScientistHead::AScientistHead()
{
}

AScientistHead::~AScientistHead()
{
}

void AScientistHead::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);

	FVector BodyPos = { 0.0f, 0.0f, 0.0f };
	FVector BodyScale = { 34.0f, 24.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	GetBody()->CreateAnimation(Anim::compo_sci_headfly1, ImgRes::compo_sci_headfly1, 0.1f, true);
	GetBody()->CreateAnimation(Anim::compo_sci_headfly2, ImgRes::compo_sci_headfly2, 0.1f, true);
	GetBody()->CreateAnimation(Anim::compo_sci_headground, ImgRes::compo_sci_headground, 0.1f, false);
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetDir(EEngineDir::Right);
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetActive(false);

	State.ChangeState(HeadState::none);
}

void AScientistHead::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AScientistHead::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadState::none);
	State.CreateState(HeadState::hurtfly);
	State.CreateState(HeadState::hurtground);
	State.CreateState(HeadState::ground);

	// State Start
	State.SetStartFunction(HeadState::none, [=] {});
	State.SetStartFunction(HeadState::hurtfly, [=] 
		{
			Velocity = { 300.0f, 800.0f, 0.0f };
			GetBody()->ChangeAnimation(Anim::compo_sci_headfly1);
			GetBody()->SetActive(true);
		}
	);

	State.SetStartFunction(HeadState::hurtground, [=] 
		{
			Velocity *= 0.4f;
			Velocity.Y *= -1.0f;
			AddActorLocation({ 0.0f, 2.0f, 0.0f});
			GetBody()->ChangeAnimation(Anim::compo_sci_headfly2);
		}
	);
	State.SetStartFunction(HeadState::ground, [=] 
		{
			Velocity = FVector::Zero;
			GetBody()->ChangeAnimation(Anim::compo_sci_headground);
			DelayCallBack(1.0f, [=] { UEngineSound::SoundPlay(SoundRes::head_bloodspurt); });
		}
	);

	// State Update
	State.SetUpdateFunction(HeadState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(HeadState::hurtfly, [=](float _DeltaTime) 
		{
			EEngineDir Dir = GetBody()->GetDir();
			if (true == IsColHeadToCeil(Dir))
			{
				Velocity.Y *= -1.0f;
			}

			if (true == IsColWall(Dir))
			{
				Velocity.X *= -1.0f;
			}
			
			// 위치 업데이트
			PosUpdate(_DeltaTime);

			if (true == IsOnGround(Dir))
			{
				State.ChangeState(HeadState::hurtground);
				return;
			}
		}
	);

	State.SetUpdateFunction(HeadState::hurtground, [=](float _DeltaTime) 
		{
			Velocity.Y -= 800.0f * _DeltaTime;

			// 위치 업데이트
			PosUpdate(_DeltaTime);

			if (true == IsOnGround(GetBody()->GetDir()))
			{
				USoundManager::SoundPlay_EnemyBloodSplat();
				State.ChangeState(HeadState::ground);
				return;
			}
		}
	);
	
	State.SetUpdateFunction(HeadState::ground, [=](float _DeltaTime) {});

}
