#include "PreCompile.h"
#include "TitleGameMode.h"

#include "TitleScreen.h"
#include "TitleMenu.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()	
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	FVector CameraStartPos = { 0.0f, 0.0f, -100.0f };
	GetWorld()->GetMainCamera()->SetActorLocation(CameraStartPos);

	FVector CameraTargetPos = { 0.0f, -360.0f, -100.0f };
	SetLerpMovePos(CameraStartPos, CameraTargetPos);

	Screen = GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");
	Menu = GetWorld()->SpawnActor<ATitleMenu>("TitleMenu");
	Menu->SetActorLocation({ 0.0f, -520.0f, 0.0f });
}

void ATitleGameMode::Intro(float _DeltaTime)
{
	if (false == IsIntroEnd)
	{
		FVector NextCameraPos = LerpMoveUpdate(_DeltaTime, IntroTimeWeight);
		GetWorld()->GetMainCamera()->SetActorLocation(NextCameraPos);
		IntroTimeWeight -= 2.0f * _DeltaTime;

		if (false == IsLerpMove())
		{
			IsIntroEnd = true;
		}
	}
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Intro(_DeltaTime);
}


