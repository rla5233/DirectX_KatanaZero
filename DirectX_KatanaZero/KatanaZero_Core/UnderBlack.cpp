#include "PreCompile.h"
#include "UnderBlack.h"

AUnderBlack::AUnderBlack()
{
}

AUnderBlack::~AUnderBlack()
{
}

void AUnderBlack::BeginPlay()
{
	Super::BeginPlay();

	GetBody()->SetSprite(ImgRes::headhunter_under_black);
	GetBody()->SetOrder(ERenderOrder::EffectBack);
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetActive(false);
}

void AUnderBlack::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(UnderBlackState::none);
	State.CreateState(UnderBlackState::on);

	// State Start
	State.SetStartFunction(UnderBlackState::none, [=] {});
	State.SetStartFunction(UnderBlackState::on, [=] 
		{
			GetBody()->SetMulColor({ 1.0f, 1.0f, 1.0f, Alpha });
			GetBody()->SetActive(true);
		}
	);

	// State Update
	State.SetUpdateFunction(UnderBlackState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(UnderBlackState::on, [=](float _DeltaTime) 
		{
			Alpha += 2.0f * _DeltaTime;

			if (1.0f < Alpha)
			{
				Alpha = 1.0f;
			}

			GetBody()->SetMulColor({ 1.0f, 1.0f, 1.0f, Alpha });
		}
	);
		
	// State End
	//State.SetEndFunction(UnderBlackState::on, [=] { SetActi })
}

void AUnderBlack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
