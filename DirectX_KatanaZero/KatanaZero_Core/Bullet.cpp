#include "PreCompile.h"
#include "Bullet.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"
#include "PlayerBase.h"

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

	State.ChangeState(BulletState::none);
}

void ABullet::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(BulletState::none);
	State.CreateState(BulletState::shoot);

	// State Start
	State.SetStartFunction(BulletState::none, [=] {});
	State.SetStartFunction(BulletState::shoot, [=]
		{
			Velocity = ShootDir;
			Velocity *= 1200.0f;

			float Deg = UContentsMath::GetAngleToAxisX2D(ShootDir);
			AddActorLocation(FVector(25.0f, 25.0f, 0.0f) * ShootDir);
			GetBody()->SetRotationDeg({ 0.0f, 0.0f, Deg });
			GetBody()->SetActive(true);
			BodyCol->SetActive(true);
		}
	);

	// State Update
	State.SetUpdateFunction(BulletState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(BulletState::shoot, [=](float _DeltaTime)
		{
			// 위치 업데이트
			PosUpdate(_DeltaTime);

			// Col Check
			FVector HeadPos = GetActorLocation() + Velocity.Normalize2DReturn() * GetBody()->GetLocalScale().hX();
			if (true == IsColPosGround(HeadPos))
			{
				GetBody()->SetActive(false);
				State.ChangeState(BulletState::none);
				return;
			}

			BodyCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
				{
					APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
					Player->HitByEnemy(ShootDir);
					GetBody()->SetActive(false);
					State.ChangeState(BulletState::none);
				}
			);

			BodyCol->CollisionEnter(EColOrder::PlayerAttack, [=](std::shared_ptr<UCollision> _Other)
				{
					GetBody()->AddRotationDeg({ 0.0f, 0.0f, 180.0f });
					Velocity *= -1.0f;
				}
			);
		}
	);

}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}


