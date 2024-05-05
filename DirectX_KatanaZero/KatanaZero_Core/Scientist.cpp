#include "PreCompile.h"
#include "Scientist.h"

#include "Factory_005.h"

AScientist::AScientist()
{
	BodyCol = CreateDefaultSubObject<UCollision>("Scientist_BodyCol");
	ExplodeEffect = CreateDefaultSubObject<USpriteRenderer>("Sci_Explode_Effect");
	
	BodyCol->SetupAttachment(GetRoot());
	ExplodeEffect->SetupAttachment(GetRoot());
}

AScientist::~AScientist()
{
}

void AScientist::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CollisionInit();
	CreateAnimation();
	InputOn();
}

void AScientist::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AScientist::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(ScientistState::idle);
	State.CreateState(ScientistState::explode);

	// State Start
	State.SetStartFunction(ScientistState::idle, [=] 
		{
			GetBody()->ChangeAnimation(Anim::compo_scientist_chair);
		}
	);

	State.SetStartFunction(ScientistState::explode, [=] 
		{
			BodyCol->SetActive(false);
			GetBody()->ChangeAnimation(Anim::compo_scientist_explode);

			// 갱스터 활성화
			AFactory_005* PlayLevel = dynamic_cast<AFactory_005*>(GetWorld()->GetGameMode().get());
			PlayLevel->ExtraGangsterOn();
		}
	);

	// State Update
	State.SetUpdateFunction(ScientistState::idle, [=](float _DeltaTime) 
		{
			if (true == IsDown(VK_SPACE))
			{
				BodyCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
					{
						State.ChangeState(ScientistState::explode);
						return;
					}
				);
			}
		}
	);

	State.SetUpdateFunction(ScientistState::explode, [=](float _DeltaTime) {});
}

void AScientist::RendererInit()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetDir(EEngineDir::Left);
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetPivot(EPivot::BOT);

	ExplodeEffect->SetOrder(ERenderOrder::EffectFront);
	ExplodeEffect->SetAutoSize(2.0f, true);
	ExplodeEffect->SetPosition({ 25.0f, 45.0f, 0.0f });
	ExplodeEffect->SetActive(false);
}

void AScientist::CollisionInit()
{
	BodyCol->SetCollisionType(ECollisionType::Rect);
	BodyCol->SetCollisionGroup(EColOrder::InteractionComponent);
	BodyCol->SetScale({ 140.0f, 40.0f, 1.0f });
	BodyCol->SetPosition({ 20.0f, 40.0f, 0.0f });
}

void AScientist::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::compo_scientist_chair, ImgRes::compo_scientist_chair, 0.1f, true);
	GetBody()->CreateAnimation(Anim::compo_scientist_explode, ImgRes::compo_scientist_explode, 0.12f, false);

	GetBody()->SetFrameCallback(Anim::compo_scientist_explode, 11, [=]
		{
			ExplodeEffect->ChangeAnimation(Anim::effect_collar_explode);
			ExplodeEffect->SetActive(true);
		}
	);

	ExplodeEffect->CreateAnimation(Anim::effect_collar_explode, ImgRes::effect_collar_explode, 0.04f, false);
	ExplodeEffect->SetLastFrameCallback(Anim::effect_collar_explode, [=] { ExplodeEffect->SetActive(false); });
}
