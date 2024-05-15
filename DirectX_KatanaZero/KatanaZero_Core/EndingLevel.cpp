#include "PreCompile.h"
#include "EndingLevel.h"

#include "EndingScreen.h"

AEndingLevel::AEndingLevel()
{
}

AEndingLevel::~AEndingLevel()
{
}

void AEndingLevel::BeginPlay()
{
	Super::BeginPlay();
}

void AEndingLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AEndingLevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	EndingScreen = GetWorld()->SpawnActor<AEndingScreen>("EndingScreen");
	EndingScreen->StateChange(EndingScrenState::fade_in);
}

void AEndingLevel::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

}
