#include "PreCompile.h"
#include "PanicSwitch.h"

#include "PlayLevelBase.h"

APanicSwitch::APanicSwitch()
{
	BodyCol = CreateDefaultSubObject<UCollision>("PanicSwitch");
	BodyCol->SetupAttachment(GetRoot());
}

APanicSwitch::~APanicSwitch()
{
}

void APanicSwitch::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CollisionInit();
	InputOn();
}

void APanicSwitch::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void APanicSwitch::RendererInit()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent);
	GetBody()->SetAutoSize(2.0f, true);
}

void APanicSwitch::CollisionInit()
{
	BodyCol->SetCollisionGroup(EColOrder::InteractionComponent);
	BodyCol->SetCollisionType(ECollisionType::Rect);
	BodyCol->SetScale({ 70.0f, 60.0f, 1.0f });
	BodyCol->SetPosition({ 0.0f, -10.0, 0.0f });
}

void APanicSwitch::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(PanicSwitch::on);
	State.CreateState(PanicSwitch::off);

	// State Start
	State.SetStartFunction(PanicSwitch::on, [=]
		{
			GetBody()->SetSprite(ImgRes::compo_panic_switch_on);
		}
	);

	State.SetStartFunction(PanicSwitch::off, [=]
		{
			GetBody()->SetSprite(ImgRes::compo_panic_switch_off);
		}
	);

	// State Update
	State.SetUpdateFunction(PanicSwitch::on, [=](float _DeltaTime)
		{
			if (true == IsDown(VK_SPACE))
			{
				BodyCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
					{
						APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
						PlayLevel->PanicSwitchOff();
						State.ChangeState(PanicSwitch::off);
						return;
					}
				);
			}
		}
	);

	State.SetUpdateFunction(PanicSwitch::off, [=](float _DeltaTime)
		{
			if (true == IsDown(VK_SPACE))
			{
				BodyCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
					{
						APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
						PlayLevel->PanicSwitchOn();
						State.ChangeState(PanicSwitch::on);
						return;
					}
				);
			}
		}
	);
}
