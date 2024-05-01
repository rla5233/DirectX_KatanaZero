#include "PreCompile.h"
#include "DiamondTransition.h"

ADiamondTransition::ADiamondTransition()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	FVector WinScale = GEngine->EngineWindow.GetWindowScale();

	AllRenderer.resize(23);
	for (size_t y = 0; y < 23; y++)
	{
		AllRenderer[y].resize(40);
		for (size_t x = 0; x < 40; x++)
		{
			AllRenderer[y][x] = CreateDefaultSubObject<USpriteRenderer>("Transition");
			
			AllRenderer[y][x]->SetupAttachment(Root);
			AllRenderer[y][x]->SetAutoSize(2.0f, true);
			AllRenderer[y][x]->SetOrder(ERenderOrder::UI);

			AllRenderer[y][x]->CreateAnimation(Anim::effect_dia_transition_on, ImgRes::effect_dia_transition, 0, 42, 0.01f, false);
			AllRenderer[y][x]->CreateAnimation(Anim::effect_dia_transition_off, ImgRes::effect_dia_transition, 43, 85, 0.01f, false);
			
			//Position
			FVector NewPos = FVector::Zero;
			NewPos.X = (32.0f * x) + 16.0f - WinScale.hX();
			NewPos.Y = 32.0f * (y - 11);
			AllRenderer[y][x]->SetPosition(NewPos);
			AllRenderer[y][x]->SetActive(false);
		}
	}

	SetRoot(Root);
}

ADiamondTransition::~ADiamondTransition()
{
}

void ADiamondTransition::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void ADiamondTransition::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_SPACE))
	{

	}
}

void ADiamondTransition::StateInit()
{
	// Create State
	State.CreateState();
}
