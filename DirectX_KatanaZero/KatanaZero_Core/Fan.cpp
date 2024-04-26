#include "PreCompile.h"
#include "Fan.h"

#include "PlayerBase.h"
#include "Factory_004.h"

AFan::AFan()
{
	Front = CreateDefaultSubObject<USpriteRenderer>("Fan_Front");
	Blade = CreateDefaultSubObject<USpriteRenderer>("Fan_Blade");
	Back = CreateDefaultSubObject<USpriteRenderer>("Fan_Back");
	BodyCol = CreateDefaultSubObject<UCollision>("Fan_Body");

	Front->SetupAttachment(GetRoot());
	Blade->SetupAttachment(GetRoot());
	Back->SetupAttachment(GetRoot());
	BodyCol->SetupAttachment(GetRoot());
}

AFan::~AFan()
{
}

void AFan::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CollisionInit();
}

void AFan::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFan::RendererInit()
{
	Back->SetSprite(ImgRes::compo_fan_back);
	Front->SetSprite(ImgRes::compo_fan_front);
	Blade->CreateAnimation(Anim::compo_fan_blade, ImgRes::compo_fan_blade, 0.004f, true);
	Blade->ChangeAnimation(Anim::compo_fan_blade);

	Blade->SetOrder(ERenderOrder::MapComponent_Back);
	Back->SetOrder(ERenderOrder::MapComponent_Back);
	Front->SetOrder(ERenderOrder::MapComponent_Front);

	Back->SetAutoSize(2.0f, true);
	Blade->SetAutoSize(2.0f, true);
	Front->SetAutoSize(2.0f, true);

	Blade->SetPosition({ 30.0f, -5.0f, 0.0f });
	Front->SetPosition({ 72.0f, 0.0f, 0.0f });
}

void AFan::CollisionInit()
{
	BodyCol->SetCollisionGroup(EColOrder::InteractionComponent);
	BodyCol->SetCollisionType(ECollisionType::Rect);
	BodyCol->SetPosition({ 50.0f, 0.0f, 0.0f });
	BodyCol->SetScale({ 20.0f, 200.0f, 1.0f });
}

void AFan::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(FanState::idle);

	// State Start
	State.SetStartFunction(FanState::idle, [=] {});

	// State Update
	State.SetUpdateFunction(FanState::idle, [=](float _DeltaTime) 
		{
			BodyCol->CollisionEnter(EColOrder::PlayerFront, [=](std::shared_ptr<UCollision> _Other)
				{
					APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
					Player->HitByEnemy(EEnemyType::Fan);
				}
			);
			
			int CurFrame = Blade->GetCurAnimationFrame();
			if (10 <= CurFrame && 29 > CurFrame)
			{
				AFactory_004* PlayLevel = dynamic_cast<AFactory_004*>(GetWorld()->GetGameMode().get());
				if (true == PlayLevel->IsPlayerAbilityOn())
				{
					BodyCol->SetActive(false);
				}

				Blade->SetPlusColor({ 0.0f, 0.0f, 0.0f });
			}

			if (10 > CurFrame || 29 <= CurFrame)
			{
				AFactory_004* PlayLevel = dynamic_cast<AFactory_004*>(GetWorld()->GetGameMode().get());
				if (true == PlayLevel->IsPlayerAbilityOn())
				{
					Blade->SetPlusColor({ 0.0f, -0.25f, -0.25f });
				}

				BodyCol->SetActive(true);
			}
		}
	);

}
