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
	BodyCol->SetScale({ 30.0f, 30.0f, 1.0f });
	BodyCol->SetPosition({ 0.0f, -10.0, 0.0f });
}

void APanicSwitch::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState("On");
	State.CreateState("Off");

	// State Start
	State.SetStartFunction("On", [=]
		{
			GetBody()->SetSprite(ImgRes::compo_panic_switch_on);
		}
	);

	State.SetStartFunction("Off", [=]
		{
			GetBody()->SetSprite(ImgRes::compo_panic_switch_off);
		}
	);

	// State Update
	State.SetUpdateFunction("On", [=](float _DeltaTime)
		{
			if (true == IsDown(VK_SPACE))
			{
				BodyCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
					{
						APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
						PlayLevel->PanicSwitchOff();
						State.ChangeState("Off");
						return;
					}
				);
			}
		}
	);

	State.SetUpdateFunction("Off", [=](float _DeltaTime)
		{
			if (true == IsDown(VK_SPACE))
			{
				BodyCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
					{
						APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
						PlayLevel->PanicSwitchOn();
						State.ChangeState("On");
						return;
					}
				);
			}
		}
	);
}
