#include "PreCompile.h"
#include "HeadHunterHead.h"

#include "HeadHunterLevel_Phase2.h"

AHeadHunterHead::AHeadHunterHead()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Head");
	Body->SetOrder(ERenderOrder::HeadHunter);
	Body->SetDir(EEngineDir::Right);
	Body->SetAutoSize(2.0f, true);
	Body->SetupAttachment(Root);

	Body->CreateAnimation(Anim::HH_head_hurtfly, ImgRes::HH_head_hurtfly, 0.1f, true);
	Body->CreateAnimation(Anim::HH_head_hurtground, ImgRes::HH_head_hurtground, 0.1f, false);

	SetRoot(Root);
}

AHeadHunterHead::~AHeadHunterHead()
{
}

void AHeadHunterHead::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);

	FVector BodyPos = { 0.0f, 0.0f, 0.0f };
	FVector BodyScale = { 26.0f, 24.0f, 0.0f };
	SetBodyInfo(BodyPos, BodyScale);

	StateInit();
}

void AHeadHunterHead::StateInit()
{
	// State Create
	State.CreateState(HeadState::none);
	State.CreateState(HeadState::hurtfly);
	State.CreateState(HeadState::hurtground);

	// State Start
	State.SetStartFunction(HeadState::none, [=] {});
	State.SetStartFunction(HeadState::hurtfly, [=] 
		{
			EEngineDir Dir = Body->GetDir();
			switch (Dir)
			{
			case EEngineDir::Left:
				Velocity = { -1200.0f, 200.0f, 0.0f };
				break;
			case EEngineDir::Right:
				Velocity = { 1200.0f, 200.0f, 0.0f };
				break;
			}

			Body->ChangeAnimation(Anim::HH_head_hurtfly);
		}
	);

	State.SetStartFunction(HeadState::hurtground, [=] 
		{
			EEngineDir Dir = Body->GetDir();
			switch (Dir)
			{
			case EEngineDir::Left:
				Velocity = { -250.0f, 200.0f, 0.0f };
				break;
			case EEngineDir::Right:
				Velocity = { 250.0f, 200.0f, 0.0f };
				break;
			}

			USoundManager::SoundPlay_EnemyBloodSplat().SetVolume(0.5f);
			Body->ChangeAnimation(Anim::HH_head_hurtground);
		}
	);

	// State Update
	State.SetUpdateFunction(HeadState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(HeadState::hurtfly, [=](float _DeltaTime) 
		{
			Velocity.Y -= 800.0f * _DeltaTime;

			// 위치 업데이트
			PosUpdate(_DeltaTime);

			EEngineDir Dir = Body->GetDir();
			if (true == IsColWall(Dir))
			{
				Velocity.X *= -0.5f;

				switch (Dir)
				{
				case EEngineDir::Left:
					while (true == IsColWall(Dir))
					{
						AddActorLocation({ 1.0f, 0.0f, 0.0f });
					}
					Body->SetDir(EEngineDir::Right);
					break;
				case EEngineDir::Right:
					while (true == IsColWall(Dir))
					{
						AddActorLocation({ -1.0f, 0.0f, 0.0f });
					}
					Body->SetDir(EEngineDir::Left);
					break;
				}
			}

			if (true == IsOnGround(Dir))
			{
				OnGroundPosAdjust(Dir);
				AddActorLocation({ 0.0f, 1.0f, 0.0f });
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

			if (true == IsOnGround(Body->GetDir()))
			{
				AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
				PlayLevel->StateChange(PlayLevelState::clear);

				USoundManager::SoundPlay_EnemyBloodSplat().SetVolume(0.5f);
				Velocity = FVector::Zero;
				State.ChangeState(HeadState::none);
				return;
			}
		}
	);

}

void AHeadHunterHead::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


