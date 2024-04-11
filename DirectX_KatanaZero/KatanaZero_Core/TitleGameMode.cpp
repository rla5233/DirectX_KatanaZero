#include "PreCompile.h"
#include "TitleGameMode.h"

#include "TitleScreen.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");
}

void ATitleGameMode::Intro(float _DeltaTime)
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}


