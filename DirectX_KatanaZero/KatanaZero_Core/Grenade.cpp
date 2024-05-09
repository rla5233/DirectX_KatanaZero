#include "PreCompile.h"
#include "Grenade.h"

AGrenade::AGrenade()
{
}

AGrenade::~AGrenade()
{
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);
	FVector BodyPos = { 0.0f, 0.0f, 0.0f };
	FVector BodyScale = { 14.0f, 18.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	GetBody()->SetSprite(ImgRes::compo_grenade);
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(1.0f, true);
	//GetBody()->SetActive(false);

	State.ChangeState(GrenadeState::none);
}

void AGrenade::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(GrenadeState::none);
	State.CreateState(GrenadeState::shoot);

	// State Start
	State.SetStartFunction(GrenadeState::none, [=] {});
	State.SetStartFunction(GrenadeState::shoot, [=] 
		{
			ShootDir = { -1.0f, 1.0f, 0.0f };
			ShootSpeed = 1000.0f;

			Velocity = ShootDir;
			Velocity *= ShootSpeed;

			if (0.0f < Velocity.X)
			{
				GetBody()->SetDir(EEngineDir::Right);
			}
			else
			{
				GetBody()->SetDir(EEngineDir::Left);
			}

			GetBody()->SetActive(true);
		}
	);

	// State Update
	State.SetUpdateFunction(GrenadeState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(GrenadeState::shoot, [=](float _DeltaTime) 
		{
			EEngineDir Dir = GetBody()->GetDir();

			// 속도 업데이트
			ApplyGravity(_DeltaTime);

			if (true == IsColWall(Dir))
			{
				switch (Dir)
				{
				case EEngineDir::Left:
					AddActorLocation({ 10.0f, 0.0f, 0.0f });
					break;
				case EEngineDir::Right:
					AddActorLocation({ -10.0f, 0.0f, 0.0f });
					break;
				}

				Velocity.X *= -0.2f;
			}

			if (true == IsOnGround(Dir))
			{
				Velocity = FVector::Zero;
			}

			// 위치 업데이트
			PosUpdate(_DeltaTime);
		}
	);

}

void AGrenade::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}