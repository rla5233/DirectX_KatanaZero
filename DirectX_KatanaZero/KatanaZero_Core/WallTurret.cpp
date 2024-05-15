#include "PreCompile.h"
#include "WallTurret.h"

#include "HeadHunterLevel_Phase2.h"

AWallTurret::AWallTurret()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->CreateAnimation(Anim::turret_wall_open, ImgRes::turret_wall_open, 0.07f, false);
	GetBody()->SetupAttachment(GetRoot());
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetActive(false);
	
	AllHolder.reserve(HolderNum);
	float InterY = 100.0f;
	for (int i = 0; i < HolderNum; i++)
	{
		AllHolder.push_back(CreateDefaultSubObject<USpriteRenderer>("Holder"));
		AllHolder[i]->SetOrder(ERenderOrder::Enemy);
		AllHolder[i]->CreateAnimation(Anim::turret_fromwall, ImgRes::turret_fromwall, 0.07f, false);
		AllHolder[i]->SetupAttachment(GetRoot());
		AllHolder[i]->SetAutoSize(2.0f, true);
		AllHolder[i]->SetActive(false);
		AllHolder[i]->SetPivot(EPivot::LEFTBOTTOM);

		AllHolder[i]->SetPosition({ -19.0f, 5.0f - InterY * i, 0.0f });
	}

	AllHead.reserve(HeadNum);
	for (int i = 0; i < HeadNum; i++)
	{
		AllHead.push_back(CreateDefaultSubObject<USpriteRenderer>("Head"));
		AllHead[i]->SetOrder(ERenderOrder::Enemy);
		AllHead[i]->SetSprite(ImgRes::turret_head);
		AllHead[i]->CreateAnimation(Anim::turret_head_die, ImgRes::turret_head_die, 0.06f, false);
		AllHead[i]->SetupAttachment(GetRoot());
		AllHead[i]->SetAutoSize(2.0f, true);
		AllHead[i]->SetActive(false);

		AllHead[i]->SetPosition({ 39.0f, 73.0f - InterY * i, 0.0f });
	}

	Spark.reserve(HeadNum);
	for (int i = 0; i < HeadNum; i++)
	{
		Spark.push_back(CreateDefaultSubObject<USpriteRenderer>("Spark"));
		Spark[i]->SetOrder(ERenderOrder::EffectFront);
		
		Spark[i]->CreateAnimation(Anim::effect_gun_spark1, ImgRes::effect_gun_spark1, 0.06f, false);
		Spark[i]->CreateAnimation(Anim::effect_gun_spark2, ImgRes::effect_gun_spark2, 0.06f, false);
		Spark[i]->CreateAnimation(Anim::effect_gun_spark3, ImgRes::effect_gun_spark3, 0.06f, false);

		Spark[i]->SetFrameCallback(Anim::effect_gun_spark1, 8, [=] { Spark[i]->SetActive(false); });
		Spark[i]->SetFrameCallback(Anim::effect_gun_spark2, 8, [=] { Spark[i]->SetActive(false); });
		Spark[i]->SetFrameCallback(Anim::effect_gun_spark3, 8, [=] { Spark[i]->SetActive(false); });

		Spark[i]->SetAutoSize(2.0f, true);
		Spark[i]->SetActive(false);
		
		Spark[i]->SetPosition({ 39.0f, 73.0f - InterY * i, 0.0f });
	}	

	HeadCol.reserve(HeadNum);
	for (int i = 0; i < HeadNum; i++)
	{
		HeadCol.push_back(CreateDefaultSubObject<UCollision>("HeadCol"));
		HeadCol[i]->SetCollisionGroup(EColOrder::InteractionComponent);
		HeadCol[i]->SetCollisionType(ECollisionType::Rect);
		HeadCol[i]->SetupAttachment(GetRoot());
		HeadCol[i]->SetActive(false);

		HeadCol[i]->SetScale({ 90.0f, 60.0f, 1.0f });
		HeadCol[i]->SetPosition({ 40.0f, 70.0f - InterY * i, 0.0f });
	}
}

AWallTurret::~AWallTurret()
{
}

void AWallTurret::BeginPlay()
{
	Super::BeginPlay();

	WallOpenAnimAdjust();

	State.ChangeState(WallTurretState::none);
}

void AWallTurret::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(WallTurretState::none);
	State.CreateState(WallTurretState::open);
	State.CreateState(WallTurretState::active);

	// State Start
	State.SetStartFunction(WallTurretState::none, [=] {});
	State.SetStartFunction(WallTurretState::open, [=] 
		{
			DelayCallBack(0.5f, [=] { UEngineSound::SoundPlay(SoundRes::hh_wallopen); });
			GetBody()->ChangeAnimation(Anim::turret_wall_open);
			GetBody()->SetActive(true);
			Order = 0;
		}
	);

	State.SetStartFunction(WallTurretState::active, [=]
		{
			for (size_t i = 0; i < HeadCol.size(); i++)
			{
				HeadCol[i]->SetActive(true);
			}
		}
	);
	
	// State Update
	State.SetUpdateFunction(WallTurretState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(WallTurretState::open, [=](float _DeltaTime) 
		{
			switch (Order)
			{
			case 0:
				if (true == GetBody()->IsCurAnimationEnd())
				{
					for (size_t i = 0; i < AllHolder.size(); i++)
					{
						AllHolder[i]->ChangeAnimation(Anim::turret_fromwall);
						AllHolder[i]->SetActive(true);
					}

					UEngineSound::SoundPlay(SoundRes::hh_wallturret_deploy);
					++Order;
				}
				break;
			case 1:
				if (true == AllHolder[0]->IsCurAnimationEnd())
				{
					State.ChangeState(WallTurretState::active);
					return;
				}
				break;
			}
		}
	);

	State.SetUpdateFunction(WallTurretState::active, [=](float _DeltaTime) 
		{
			AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
			FVector PlayerPos = PlayLevel->GetPlayerLocation();

			for (size_t i = 0; i < AllHead.size(); i++)
			{
				// Collision Update
				HeadCol[i]->CollisionEnter(EColOrder::PlayerAttack, [=](std::shared_ptr<UCollision> _Other)
					{
						UEngineSound::SoundPlay(SoundRes::hh_wallturret_dead);
						AllHolder[i]->AnimationReset();
						AllHolder[i]->SetSprite(ImgRes::turret_holder);
						AllHead[i]->ChangeAnimation(Anim::turret_head_die);
						AllHead[i]->AddPosition({ -23.0f, 4.0f, 0.0f });
						AllHead[i]->SetRotationDeg(FVector::Zero);
						HeadCol[i]->SetActive(false);
					}
				);

				FVector HeadPos = AllHead[i]->GetWorldPosition();
				FVector HeadDir = (PlayerPos - HeadPos).Normalize2DReturn();

				if (false == HeadCol[i]->IsActive() || MinHeadRangeX[i] > PlayerPos.X)
				{
					continue;
				}
				
				// Deg Update
				float Deg =  UContentsMath::GetAngleToX_2D(HeadDir);
				if (HeadDeg_Min > Deg)
				{
					if (HeadPos.Y < PlayerPos.Y)
					{
						Deg = 0.0f;
					}
					else
					{
						Deg = HeadDeg_Min;
					}
				}

				AllHead[i]->SetRotationDeg({ 0.0f, 0.0f, Deg });

				// Shoot Update
				if (0.0f < ShootDelayTimeCount[i] || true == PlayLevel->IsPlayerDead())
				{
					ShootDelayTimeCount[i] -= _DeltaTime;
				}
				else
				{
					// Bullet
					FVector BulletPos = FVector(HeadPos.X, HeadPos.Y + 16.0f, 0.0f) + FVector(100.0f, 100.0f, 0.0f) * HeadDir;
					USoundManager::SoundPlay_GunFire();
					UEngineSound::SoundPlay(SoundRes::hh_wallturret_overheat);
					PlayLevel->SetShootBullet(BulletPos, HeadDir);
					ShootDelayTimeCount[i] = ShootDelayTime;

					// Spark
					Spark[i]->AnimationReset();

					int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
					switch (RandomValue)
					{
					case 1:
						Spark[i]->ChangeAnimation(Anim::effect_gun_spark1);
						break;
					case 2:
						Spark[i]->ChangeAnimation(Anim::effect_gun_spark2);
						break;
					case 3:
						Spark[i]->ChangeAnimation(Anim::effect_gun_spark3);
						break;
					}

					FVector SparkPos = FVector(50.0f, 50.0f, 0.0f) * HeadDir;
					Spark[i]->SetRotationDeg({ 0.0f, 0.0f, Deg });
					Spark[i]->SetPosition(BulletPos);
					Spark[i]->SetActive(true);
				}
			}
		}
	);

}

void AWallTurret::WallOpenAnimAdjust()
{
	// Wall
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 0,	[=] { GetBody()->SetPosition({ 0.0f, 0.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 1,	[=] { GetBody()->SetPosition({ 0.0f, -2.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 2,	[=] { GetBody()->SetPosition({ 0.0f, -10.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 3,	[=] { GetBody()->SetPosition({ 0.0f, -12.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 4,	[=] { GetBody()->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 5,	[=] { GetBody()->SetPosition({ 0.0f, -18.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 6,	[=] { GetBody()->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 7,	[=] { GetBody()->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 8,	[=] { GetBody()->SetPosition({ 0.0f, 1.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 14,	[=] { GetBody()->SetPosition({ 0.0f, -2.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 15,	[=] { GetBody()->SetPosition({ 0.0f, -5.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 16,	[=] { GetBody()->SetPosition({ 0.0f, -4.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 19,	[=] { GetBody()->SetPosition({ 0.0f, 3.0f, 0.0f }); });

	// Holder
	for (size_t i = 0; i < AllHolder.size(); i++)
	{
		AllHolder[i]->SetLastFrameCallback(Anim::turret_fromwall, [=] { AllHead[i]->SetActive(true); });
	}
}

void AWallTurret::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWallTurret::SetAllMulColor(const float4& _MulColor)
{
	Super::SetAllMulColor(_MulColor);

	for (size_t i = 0; i < HeadNum; i++)
	{
		AllHolder[i]->SetMulColor(_MulColor);
		AllHead[i]->SetMulColor(_MulColor);
	}
}

void AWallTurret::SetEndingMulColor(const float4& _MulColor)
{
	for (size_t i = 0; i < HeadNum; i++)
	{
		AllHolder[i]->SetMulColor(_MulColor);
		AllHead[i]->SetMulColor(_MulColor);
		GetBody()->SetMulColor(_MulColor);
	}
}