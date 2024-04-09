#include "PreCompile.h"
#include "TitleScreen.h"

#include "Constant.h"

ATitleScreen::ATitleScreen()
{
	Plants		= CreateDefaultSubObject<USpriteRenderer>("Plants");
	Fence		= CreateDefaultSubObject<USpriteRenderer>("Fence");
	BackGround	= CreateDefaultSubObject<USpriteRenderer>("BackGround");
}

ATitleScreen::~ATitleScreen()
{
} 

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, 0.0f, 0.0f });
	SetActorScale3D({ 1280.0f, 1440.0f, 1.0f });

	StateChange(ETitleState::Intro);
}

void ATitleScreen::IntroStart()
{
	Plants->SetSprite(ImgRes::title_plant);
	Fence->SetSprite(ImgRes::title_fence);
	BackGround->SetSprite(ImgRes::title_background);
	
	BackGround->Transform.SetScale({ 1280.0f, 1440.0f, 1.0f });
	Fence->Transform.SetScale({ 1280.0f, 1440.0f, 1.0f });
	Plants->Transform.SetScale({ 1280.0f, 510.0f, 1.0f });
	Plants->Transform.SetPosition({ 0.0f, -465.0f, 0.0f });

	Plants->CreateAnimation("Plants", ImgRes::title_plant, 0.1f, true, 0, 11);
	Plants->ChangeAnimation("Plants");

	FVector StartPos = GetActorLocation();
	FVector TargetPos = StartPos + FVector(0.0f, -500.0f, 0.0f);
	SetLerpMovePos(StartPos, TargetPos);
}

void ATitleScreen::Intro(float _DeltaTime)
{
	IntroAnimation(_DeltaTime);
}

void ATitleScreen::IntroAnimation(float _DeltaTime)
{
	FVector NextPos = LerpMoveUpdate(_DeltaTime);
	SetActorLocation(NextPos);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ATitleScreen::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ETitleState::Intro:
		Intro(_DeltaTime);
		break;
	case ETitleState::Select:
		break;
	}
}

void ATitleScreen::StateChange(ETitleState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ETitleState::Intro:
			IntroStart();
			break;
		case ETitleState::Select:
			break;
		}
	}

	State = _State;
}