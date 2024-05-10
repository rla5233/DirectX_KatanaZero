#include "PreCompile.h"
#include "Bullet.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"

ABullet::ABullet()
{
	BodyCol = CreateDefaultSubObject<UCollision>("Bullet_Col");
	BodyCol->SetCollisionGroup(EColOrder::EnemyAttack);
	BodyCol->SetCollisionType(ECollisionType::RotRect);
	BodyCol->SetupAttachment(GetBody());
	BodyCol->SetActive(false);
}

ABullet::~ABullet()
{
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);

	GetBody()->SetSprite(ImgRes::compo_bullet1);
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(1.0f, true);
	GetBody()->SetActive(false);

	State.ChangeState(GrenadeState::none);
}

void ABullet::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(GrenadeState::none);
	State.CreateState(GrenadeState::shoot);

	// State Start
	State.SetStartFunction(GrenadeState::none, [=] {});
	State.SetStartFunction(GrenadeState::shoot, [=] 
		{
			Velocity = ShootDir;
			Velocity *= 1200.0f;

			float Deg = UContentsMath::GetAngleToX_2D(ShootDir);
			AddActorLocation(FVector(25.0f, 25.0f, 0.0f) * ShootDir);
			GetBody()->SetRotationDeg({ 0.0f, 0.0f, Deg });
			GetBody()->SetActive(true);
			BodyCol->SetActive(true);
		}
	);

	// State Update
	State.SetUpdateFunction(GrenadeState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(GrenadeState::shoot, [=](float _DeltaTime) 
		{
			// 위치 업데이트
			PosUpdate(_DeltaTime);

			// Col Check
			FVector HeadPos = GetActorLocation() + ShootDir * GetBody()->GetLocalScale().hX();
			if (true == IsColPosGround(HeadPos))
			{
				GetBody()->SetActive(false);
			}
		}
	);

}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}


