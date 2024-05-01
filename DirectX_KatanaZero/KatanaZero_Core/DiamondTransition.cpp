#include "PreCompile.h"
#include "DiamondTransition.h"

ADiamondTransition::ADiamondTransition()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	FVector WinScale = GEngine->EngineWindow.GetWindowScale();

	AllRenderer.resize(Height);
	for (size_t y = 0; y < Height; y++)
	{
		AllRenderer[y].resize(Width);
		for (size_t x = 0; x < Width; x++)
		{
			AllRenderer[y][x] = CreateDefaultSubObject<USpriteRenderer>("Transition");
			
			AllRenderer[y][x]->SetupAttachment(Root);
			AllRenderer[y][x]->SetAutoSize(2.0f, true);
			AllRenderer[y][x]->SetOrder(ERenderOrder::UI);

			AllRenderer[y][x]->CreateAnimation(Anim::effect_dia_transition_on, ImgRes::effect_dia_transition, 0.01f, false, 0, 42);
			AllRenderer[y][x]->CreateAnimation(Anim::effect_dia_transition_off, ImgRes::effect_dia_transition, 0.01f, false, 43, 85);
			AllRenderer[y][x]->SetLastFrameCallback(Anim::effect_dia_transition_off, [=] {	AllRenderer[y][x]->SetActive(false); });
			
			//Position
			FVector NewPos = FVector::Zero;
			NewPos.X = (32.0f * x) + 16.0f - WinScale.hX();
			NewPos.Y = WinScale.hY() + 8 - (32.0f * y);
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
	State.ChangeState(DiaTransitionState::none);
}

void ADiamondTransition::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		if (DiaTransitionState::on != State.GetCurStateName())
		{
			State.ChangeState(DiaTransitionState::on);
			return;
		}

		if (DiaTransitionState::off != State.GetCurStateName())
		{
			State.ChangeState(DiaTransitionState::off);
			return;
		}
	}
}

void ADiamondTransition::StateInit()
{
	// State Create 
	State.CreateState(DiaTransitionState::none);
	State.CreateState(DiaTransitionState::on);
	State.CreateState(DiaTransitionState::off);

	// State Start
	State.SetStartFunction(DiaTransitionState::none, [=] {});
	State.SetStartFunction(DiaTransitionState::on, [=]
		{
			FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
			CameraPos.Z = 0.0f;
			SetActorLocation(CameraPos);

			X = Width - 1;
		}
	);

	State.SetStartFunction(DiaTransitionState::off, [=]
		{
			FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
			CameraPos.Z = 0.0f;
			SetActorLocation(CameraPos);

			X = Width - 1;
		}
	);

	// State Update
	State.SetUpdateFunction(DiaTransitionState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(DiaTransitionState::on, [=](float _DeltaTime)
		{
			if (0.0f < TimeCount || 0 > X)
			{
				TimeCount -= _DeltaTime;
				return;
			}

			for (size_t y = 0; y < Height; y++)
			{
				AllRenderer[y][X]->SetActive(true);
				AllRenderer[y][X]->ChangeAnimation(Anim::effect_dia_transition_on);
			}

			TimeCount = Const::effect_dia_transition_delay;
			--X;
		}
	);

	State.SetUpdateFunction(DiaTransitionState::off, [=](float _DeltaTime)
		{
			if (0.0f < TimeCount || 0 > X)
			{
				TimeCount -= _DeltaTime;
				return;
			}

			for (size_t y = 0; y < Height; y++)
			{
				AllRenderer[y][X]->SetActive(true);
				AllRenderer[y][X]->ChangeAnimation(Anim::effect_dia_transition_off);
			}

			TimeCount = Const::effect_dia_transition_delay;
			--X;
		}
	);
}
